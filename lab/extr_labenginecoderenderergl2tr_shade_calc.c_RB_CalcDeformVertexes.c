#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_7__ {scalar_t__ frequency; scalar_t__ phase; int /*<<< orphan*/  amplitude; int /*<<< orphan*/  base; int /*<<< orphan*/  func; } ;
struct TYPE_5__ {float deformationSpread; TYPE_4__ deformationWave; } ;
typedef  TYPE_1__ deformStage_t ;
struct TYPE_6__ {int numVertexes; int /*<<< orphan*/ ** normal; scalar_t__ xyz; } ;

/* Variables and functions */
 float EvalWaveForm (TYPE_4__*) ; 
 int /*<<< orphan*/  R_VaoUnpackNormal (float*,int /*<<< orphan*/ *) ; 
 float* TableForFunc (int /*<<< orphan*/ ) ; 
 float WAVEVALUE (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_2__ tess ; 

void RB_CalcDeformVertexes( deformStage_t *ds )
{
	int i;
	vec3_t	offset;
	float	scale;
	float	*xyz = ( float * ) tess.xyz;
	int16_t	*normal = tess.normal[0];
	float	*table;

	if ( ds->deformationWave.frequency == 0 )
	{
		scale = EvalWaveForm( &ds->deformationWave );

		for ( i = 0; i < tess.numVertexes; i++, xyz += 4, normal += 4 )
		{
			R_VaoUnpackNormal(offset, normal);
			
			xyz[0] += offset[0] * scale;
			xyz[1] += offset[1] * scale;
			xyz[2] += offset[2] * scale;
		}
	}
	else
	{
		table = TableForFunc( ds->deformationWave.func );

		for ( i = 0; i < tess.numVertexes; i++, xyz += 4, normal += 4 )
		{
			float off = ( xyz[0] + xyz[1] + xyz[2] ) * ds->deformationSpread;

			scale = WAVEVALUE( table, ds->deformationWave.base, 
				ds->deformationWave.amplitude,
				ds->deformationWave.phase + off,
				ds->deformationWave.frequency );

			R_VaoUnpackNormal(offset, normal);

			xyz[0] += offset[0] * scale;
			xyz[1] += offset[1] * scale;
			xyz[2] += offset[2] * scale;
		}
	}
}