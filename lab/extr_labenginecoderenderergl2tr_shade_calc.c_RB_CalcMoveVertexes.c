#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {int /*<<< orphan*/  frequency; int /*<<< orphan*/  phase; int /*<<< orphan*/  amplitude; int /*<<< orphan*/  base; int /*<<< orphan*/  func; } ;
struct TYPE_6__ {int /*<<< orphan*/  moveVector; TYPE_1__ deformationWave; } ;
typedef  TYPE_2__ deformStage_t ;
struct TYPE_7__ {int numVertexes; scalar_t__ xyz; } ;

/* Variables and functions */
 float* TableForFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorAdd (float*,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 float WAVEVALUE (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ tess ; 

void RB_CalcMoveVertexes( deformStage_t *ds ) {
	int			i;
	float		*xyz;
	float		*table;
	float		scale;
	vec3_t		offset;

	table = TableForFunc( ds->deformationWave.func );

	scale = WAVEVALUE( table, ds->deformationWave.base, 
		ds->deformationWave.amplitude,
		ds->deformationWave.phase,
		ds->deformationWave.frequency );

	VectorScale( ds->moveVector, scale, offset );

	xyz = ( float * ) tess.xyz;
	for ( i = 0; i < tess.numVertexes; i++, xyz += 4 ) {
		VectorAdd( xyz, offset, xyz );
	}
}