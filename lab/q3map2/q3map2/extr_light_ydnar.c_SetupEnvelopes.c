#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_10__ {float photons; float add; int flags; scalar_t__ type; scalar_t__ cluster; float envelope; scalar_t__* mins; scalar_t__* maxs; scalar_t__* origin; scalar_t__* normal; float falloffTolerance; float fade; int envelope2; size_t style; struct TYPE_10__* next; struct TYPE_10__* w; TYPE_1__* si; } ;
typedef  TYPE_2__ light_t ;
typedef  int /*<<< orphan*/  buckets ;
struct TYPE_11__ {scalar_t__ cluster; scalar_t__* mins; scalar_t__* maxs; } ;
typedef  TYPE_3__ bspLeaf_t ;
struct TYPE_9__ {scalar_t__ noFast; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ChopBounds (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ClearBounds (scalar_t__*,scalar_t__*) ; 
 void* ClusterForPointExt (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ClusterVisible (scalar_t__,scalar_t__) ; 
 scalar_t__ EMIT_AREA ; 
 scalar_t__ EMIT_SPOT ; 
 scalar_t__ EMIT_SUN ; 
 int LIGHT_ATTEN_DISTANCE ; 
 int LIGHT_ATTEN_LINEAR ; 
 int /*<<< orphan*/  LIGHT_EPSILON ; 
 int LIGHT_FAST ; 
 int LIGHT_FAST_TEMP ; 
 int LIGHT_GRID ; 
 int LIGHT_NEGATIVE ; 
 int LIGHT_NUDGE ; 
 int LIGHT_SURFACES ; 
 size_t LS_NORMAL ; 
 float MAX_WORLD_COORD ; 
 float MIN_WORLD_COORD ; 
 float PointToPolygonFormFactor (scalar_t__*,scalar_t__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  Sys_Printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 scalar_t__ VectorLength (scalar_t__*) ; 
 int /*<<< orphan*/  VectorMA (scalar_t__*,float,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorScale (scalar_t__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  VectorSet (scalar_t__*,float,float,float) ; 
 int /*<<< orphan*/  VectorSubtract (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 TYPE_3__* bspLeafs ; 
 scalar_t__ exactPointToPolygon ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* lights ; 
 float linearScale ; 
 int /*<<< orphan*/  memset (TYPE_2__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  noCollapse ; 
 int numBSPLeafs ; 
 scalar_t__ numCulledLights ; 
 scalar_t__ numLights ; 
 scalar_t__ qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 float sqrt (float) ; 

void SetupEnvelopes( qboolean forGrid, qboolean fastFlag ){
	int i, x, y, z, x1, y1, z1;
	light_t     *light, *light2, **owner;
	bspLeaf_t   *leaf;
	vec3_t origin, dir, mins, maxs;
	float radius, intensity;
	light_t     *buckets[ 256 ];


	/* early out for weird cases where there are no lights */
	if ( lights == NULL ) {
		return;
	}

	/* note it */
	Sys_FPrintf( SYS_VRB, "--- SetupEnvelopes%s ---\n", fastFlag ? " (fast)" : "" );

	/* count lights */
	numLights = 0;
	numCulledLights = 0;
	owner = &lights;
	while ( *owner != NULL )
	{
		/* get light */
		light = *owner;

		/* handle negative lights */
		if ( light->photons < 0.0f || light->add < 0.0f ) {
			light->photons *= -1.0f;
			light->add *= -1.0f;
			light->flags |= LIGHT_NEGATIVE;
		}

		/* sunlight? */
		if ( light->type == EMIT_SUN ) {
			/* special cased */
			light->cluster = 0;
			light->envelope = MAX_WORLD_COORD * 8.0f;
			VectorSet( light->mins, MIN_WORLD_COORD * 8.0f, MIN_WORLD_COORD * 8.0f, MIN_WORLD_COORD * 8.0f );
			VectorSet( light->maxs, MAX_WORLD_COORD * 8.0f, MAX_WORLD_COORD * 8.0f, MAX_WORLD_COORD * 8.0f );
		}

		/* everything else */
		else
		{
			/* get pvs cluster for light */
			light->cluster = ClusterForPointExt( light->origin, LIGHT_EPSILON );

			/* invalid cluster? */
			if ( light->cluster < 0 ) {
				/* nudge the sample point around a bit */
				for ( x = 0; x < 4; x++ )
				{
					/* two's complement 0, 1, -1, 2, -2, etc */
					x1 = ( ( x >> 1 ) ^ ( x & 1 ? -1 : 0 ) ) + ( x & 1 );

					for ( y = 0; y < 4; y++ )
					{
						y1 = ( ( y >> 1 ) ^ ( y & 1 ? -1 : 0 ) ) + ( y & 1 );

						for ( z = 0; z < 4; z++ )
						{
							z1 = ( ( z >> 1 ) ^ ( z & 1 ? -1 : 0 ) ) + ( z & 1 );

							/* nudge origin */
							origin[ 0 ] = light->origin[ 0 ] + ( LIGHT_NUDGE * x1 );
							origin[ 1 ] = light->origin[ 1 ] + ( LIGHT_NUDGE * y1 );
							origin[ 2 ] = light->origin[ 2 ] + ( LIGHT_NUDGE * z1 );

							/* try at nudged origin */
							light->cluster = ClusterForPointExt( origin, LIGHT_EPSILON );
							if ( light->cluster < 0 ) {
								continue;
							}

							/* set origin */
							VectorCopy( origin, light->origin );
						}
					}
				}
			}

			/* only calculate for lights in pvs and outside of opaque brushes */
			if ( light->cluster >= 0 ) {
				/* set light fast flag */
				if ( fastFlag ) {
					light->flags |= LIGHT_FAST_TEMP;
				}
				else{
					light->flags &= ~LIGHT_FAST_TEMP;
				}
				if ( light->si && light->si->noFast ) {
					light->flags &= ~( LIGHT_FAST | LIGHT_FAST_TEMP );
				}

				/* clear light envelope */
				light->envelope = 0;

				/* handle area lights */
				if ( exactPointToPolygon && light->type == EMIT_AREA && light->w != NULL ) {
					/* ugly hack to calculate extent for area lights, but only done once */
					VectorScale( light->normal, -1.0f, dir );
					for ( radius = 100.0f; radius < 130000.0f && light->envelope == 0; radius += 10.0f )
					{
						float factor;

						VectorMA( light->origin, radius, light->normal, origin );
						factor = PointToPolygonFormFactor( origin, dir, light->w );
						if ( factor < 0.0f ) {
							factor *= -1.0f;
						}
						if ( ( factor * light->add ) <= light->falloffTolerance ) {
							light->envelope = radius;
						}
					}

					/* check for fast mode */
					if ( !( light->flags & LIGHT_FAST ) && !( light->flags & LIGHT_FAST_TEMP ) ) {
						light->envelope = MAX_WORLD_COORD * 8.0f;
					}
				}
				else
				{
					radius = 0.0f;
					intensity = light->photons;
				}

				/* other calcs */
				if ( light->envelope <= 0.0f ) {
					/* solve distance for non-distance lights */
					if ( !( light->flags & LIGHT_ATTEN_DISTANCE ) ) {
						light->envelope = MAX_WORLD_COORD * 8.0f;
					}

					/* solve distance for linear lights */
					else if ( ( light->flags & LIGHT_ATTEN_LINEAR ) ) {
						//% light->envelope = ((intensity / light->falloffTolerance) * linearScale - 1 + radius) / light->fade;
						light->envelope = ( ( intensity * linearScale ) - light->falloffTolerance ) / light->fade;
					}

					/*
					   add = angle * light->photons * linearScale - (dist * light->fade);
					   T = (light->photons * linearScale) - (dist * light->fade);
					   T + (dist * light->fade) = (light->photons * linearScale);
					   dist * light->fade = (light->photons * linearScale) - T;
					   dist = ((light->photons * linearScale) - T) / light->fade;
					 */

					/* solve for inverse square falloff */
					else{
						light->envelope = sqrt( intensity / light->falloffTolerance ) + radius;
					}

					/*
					   add = light->photons / (dist * dist);
					   T = light->photons / (dist * dist);
					   T * (dist * dist) = light->photons;
					   dist = sqrt( light->photons / T );
					 */
				}

				/* chop radius against pvs */
				{
					/* clear bounds */
					ClearBounds( mins, maxs );

					/* check all leaves */
					for ( i = 0; i < numBSPLeafs; i++ )
					{
						/* get test leaf */
						leaf = &bspLeafs[ i ];

						/* in pvs? */
						if ( leaf->cluster < 0 ) {
							continue;
						}
						if ( ClusterVisible( light->cluster, leaf->cluster ) == qfalse ) { /* ydnar: thanks Arnout for exposing my stupid error (this never failed before) */
							continue;
						}

						/* add this leafs bbox to the bounds */
						VectorCopy( leaf->mins, origin );
						AddPointToBounds( origin, mins, maxs );
						VectorCopy( leaf->maxs, origin );
						AddPointToBounds( origin, mins, maxs );
					}

					/* test to see if bounds encompass light */
					for ( i = 0; i < 3; i++ )
					{
						if ( mins[ i ] > light->origin[ i ] || maxs[ i ] < light->origin[ i ] ) {
							//% Sys_FPrintf( SYS_WRN, "WARNING: Light PVS bounds (%.0f, %.0f, %.0f) -> (%.0f, %.0f, %.0f)\ndo not encompass light %d (%f, %f, %f)\n",
							//%     mins[ 0 ], mins[ 1 ], mins[ 2 ],
							//%     maxs[ 0 ], maxs[ 1 ], maxs[ 2 ],
							//%     numLights, light->origin[ 0 ], light->origin[ 1 ], light->origin[ 2 ] );
							AddPointToBounds( light->origin, mins, maxs );
						}
					}

					/* chop the bounds by a plane for area lights and spotlights */
					if ( light->type == EMIT_AREA || light->type == EMIT_SPOT ) {
						ChopBounds( mins, maxs, light->origin, light->normal );
					}

					/* copy bounds */
					VectorCopy( mins, light->mins );
					VectorCopy( maxs, light->maxs );

					/* reflect bounds around light origin */
					//%	VectorMA( light->origin, -1.0f, origin, origin );
					VectorScale( light->origin, 2, origin );
					VectorSubtract( origin, maxs, origin );
					AddPointToBounds( origin, mins, maxs );
					//%	VectorMA( light->origin, -1.0f, mins, origin );
					VectorScale( light->origin, 2, origin );
					VectorSubtract( origin, mins, origin );
					AddPointToBounds( origin, mins, maxs );

					/* calculate spherical bounds */
					VectorSubtract( maxs, light->origin, dir );
					radius = (float) VectorLength( dir );

					/* if this radius is smaller than the envelope, then set the envelope to it */
					if ( radius < light->envelope ) {
						light->envelope = radius;
						//%	Sys_FPrintf( SYS_VRB, "PVS Cull (%d): culled\n", numLights );
					}
					//%	else
					//%		Sys_FPrintf( SYS_VRB, "PVS Cull (%d): failed (%8.0f > %8.0f)\n", numLights, radius, light->envelope );
				}

				/* add grid/surface only check */
				if ( forGrid ) {
					if ( !( light->flags & LIGHT_GRID ) ) {
						light->envelope = 0.0f;
					}
				}
				else
				{
					if ( !( light->flags & LIGHT_SURFACES ) ) {
						light->envelope = 0.0f;
					}
				}
			}

			/* culled? */
			if ( light->cluster < 0 || light->envelope <= 0.0f ) {
				/* debug code */
				//%	Sys_Printf( "Culling light: Cluster: %d Envelope: %f\n", light->cluster, light->envelope );

				/* delete the light */
				numCulledLights++;
				*owner = light->next;
				if ( light->w != NULL ) {
					free( light->w );
				}
				free( light );
				continue;
			}
		}

		/* square envelope */
		light->envelope2 = ( light->envelope * light->envelope );

		/* increment light count */
		numLights++;

		/* set next light */
		owner = &( ( **owner ).next );
	}

	/* bucket sort lights by style */
	memset( buckets, 0, sizeof( buckets ) );
	light2 = NULL;
	for ( light = lights; light != NULL; light = light2 )
	{
		/* get next light */
		light2 = light->next;

		/* filter into correct bucket */
		light->next = buckets[ light->style ];
		buckets[ light->style ] = light;

		/* if any styled light is present, automatically set nocollapse */
		if ( light->style != LS_NORMAL ) {
			noCollapse = qtrue;
		}
	}

	/* filter back into light list */
	lights = NULL;
	for ( i = 255; i >= 0; i-- )
	{
		light2 = NULL;
		for ( light = buckets[ i ]; light != NULL; light = light2 )
		{
			light2 = light->next;
			light->next = lights;
			lights = light;
		}
	}

	/* emit some statistics */
	Sys_Printf( "%9d total lights\n", numLights );
	Sys_Printf( "%9d culled lights\n", numCulledLights );
}