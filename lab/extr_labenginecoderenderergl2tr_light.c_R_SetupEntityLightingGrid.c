#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float* lightGridInverseSize; int* lightGridBounds; float* lightGridData; float* lightGrid16; int /*<<< orphan*/  lightGridOrigin; } ;
typedef  TYPE_2__ world_t ;
typedef  float* vec3_t ;
typedef  float uint16_t ;
struct TYPE_9__ {int renderfx; int /*<<< orphan*/  origin; int /*<<< orphan*/  lightingOrigin; } ;
struct TYPE_11__ {float* ambientLight; float* directedLight; int /*<<< orphan*/  lightDir; TYPE_1__ e; } ;
typedef  TYPE_3__ trRefEntity_t ;
typedef  float byte ;
struct TYPE_14__ {float value; } ;
struct TYPE_13__ {float value; } ;
struct TYPE_12__ {float* sinTable; } ;

/* Variables and functions */
 int FUNCTABLE_MASK ; 
 int FUNCTABLE_SIZE ; 
 int RF_LIGHTING_ORIGIN ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  VectorMA (float*,float,float*,float*) ; 
 int /*<<< orphan*/  VectorNormalize2 (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  assert (float*) ; 
 int floor (float) ; 
 TYPE_6__* r_ambientScale ; 
 TYPE_5__* r_directedScale ; 
 TYPE_4__ tr ; 

__attribute__((used)) static void R_SetupEntityLightingGrid( trRefEntity_t *ent, world_t *world ) {
	vec3_t	lightOrigin;
	int		pos[3];
	int		i, j;
	byte	*gridData;
	float	frac[3];
	int		gridStep[3];
	vec3_t	direction;
	float	totalFactor;

	if ( ent->e.renderfx & RF_LIGHTING_ORIGIN ) {
		// separate lightOrigins are needed so an object that is
		// sinking into the ground can still be lit, and so
		// multi-part models can be lit identically
		VectorCopy( ent->e.lightingOrigin, lightOrigin );
	} else {
		VectorCopy( ent->e.origin, lightOrigin );
	}

	VectorSubtract( lightOrigin, world->lightGridOrigin, lightOrigin );
	for ( i = 0 ; i < 3 ; i++ ) {
		float	v;

		v = lightOrigin[i]*world->lightGridInverseSize[i];
		pos[i] = floor( v );
		frac[i] = v - pos[i];
		if ( pos[i] < 0 ) {
			pos[i] = 0;
		} else if ( pos[i] > world->lightGridBounds[i] - 1 ) {
			pos[i] = world->lightGridBounds[i] - 1;
		}
	}

	VectorClear( ent->ambientLight );
	VectorClear( ent->directedLight );
	VectorClear( direction );

	assert( world->lightGridData ); // NULL with -nolight maps

	// trilerp the light value
	gridStep[0] = 8;
	gridStep[1] = 8 * world->lightGridBounds[0];
	gridStep[2] = 8 * world->lightGridBounds[0] * world->lightGridBounds[1];
	gridData = world->lightGridData + pos[0] * gridStep[0]
		+ pos[1] * gridStep[1] + pos[2] * gridStep[2];

	totalFactor = 0;
	for ( i = 0 ; i < 8 ; i++ ) {
		float	factor;
		byte	*data;
		int		lat, lng;
		vec3_t	normal;
		#if idppc
		float d0, d1, d2, d3, d4, d5;
		#endif
		factor = 1.0;
		data = gridData;
		for ( j = 0 ; j < 3 ; j++ ) {
			if ( i & (1<<j) ) {
				if ( pos[j] + 1 > world->lightGridBounds[j] - 1 ) {
					break; // ignore values outside lightgrid
				}
				factor *= frac[j];
				data += gridStep[j];
			} else {
				factor *= (1.0f - frac[j]);
			}
		}

		if ( j != 3 ) {
			continue;
		}

		if (world->lightGrid16)
		{
			uint16_t *data16 = world->lightGrid16 + (int)(data - world->lightGridData) / 8 * 6;
			if (!(data16[0]+data16[1]+data16[2]+data16[3]+data16[4]+data16[5])) {
				continue;	// ignore samples in walls
			}
		}
		else
		{
			if (!(data[0]+data[1]+data[2]+data[3]+data[4]+data[5]) ) {
				continue;	// ignore samples in walls
			}
		}
		totalFactor += factor;
		#if idppc
		d0 = data[0]; d1 = data[1]; d2 = data[2];
		d3 = data[3]; d4 = data[4]; d5 = data[5];

		ent->ambientLight[0] += factor * d0;
		ent->ambientLight[1] += factor * d1;
		ent->ambientLight[2] += factor * d2;

		ent->directedLight[0] += factor * d3;
		ent->directedLight[1] += factor * d4;
		ent->directedLight[2] += factor * d5;
		#else
		if (world->lightGrid16)
		{
			// FIXME: this is hideous
			uint16_t *data16 = world->lightGrid16 + (int)(data - world->lightGridData) / 8 * 6;

			ent->ambientLight[0] += factor * data16[0] / 257.0f;
			ent->ambientLight[1] += factor * data16[1] / 257.0f;
			ent->ambientLight[2] += factor * data16[2] / 257.0f;

			ent->directedLight[0] += factor * data16[3] / 257.0f;
			ent->directedLight[1] += factor * data16[4] / 257.0f;
			ent->directedLight[2] += factor * data16[5] / 257.0f;
		}
		else
		{
			ent->ambientLight[0] += factor * data[0];
			ent->ambientLight[1] += factor * data[1];
			ent->ambientLight[2] += factor * data[2];

			ent->directedLight[0] += factor * data[3];
			ent->directedLight[1] += factor * data[4];
			ent->directedLight[2] += factor * data[5];
		}
		#endif
		lat = data[7];
		lng = data[6];
		lat *= (FUNCTABLE_SIZE/256);
		lng *= (FUNCTABLE_SIZE/256);

		// decode X as cos( lat ) * sin( long )
		// decode Y as sin( lat ) * sin( long )
		// decode Z as cos( long )

		normal[0] = tr.sinTable[(lat+(FUNCTABLE_SIZE/4))&FUNCTABLE_MASK] * tr.sinTable[lng];
		normal[1] = tr.sinTable[lat] * tr.sinTable[lng];
		normal[2] = tr.sinTable[(lng+(FUNCTABLE_SIZE/4))&FUNCTABLE_MASK];

		VectorMA( direction, factor, normal, direction );
	}

	if ( totalFactor > 0 && totalFactor < 0.99 ) {
		totalFactor = 1.0f / totalFactor;
		VectorScale( ent->ambientLight, totalFactor, ent->ambientLight );
		VectorScale( ent->directedLight, totalFactor, ent->directedLight );
	}

	VectorScale( ent->ambientLight, r_ambientScale->value, ent->ambientLight );
	VectorScale( ent->directedLight, r_directedScale->value, ent->directedLight );

	VectorNormalize2( direction, ent->lightDir );
}