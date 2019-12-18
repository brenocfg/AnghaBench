#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int64_t ;
struct TYPE_8__ {double bulgeSpeed; float const bulgeWidth; float bulgeHeight; } ;
typedef  TYPE_2__ deformStage_t ;
struct TYPE_7__ {double time; } ;
struct TYPE_11__ {TYPE_1__ refdef; } ;
struct TYPE_10__ {int numVertexes; scalar_t__ normal; scalar_t__ xyz; scalar_t__* texCoords; } ;
struct TYPE_9__ {float* sinTable; } ;

/* Variables and functions */
 size_t FUNCTABLE_MASK ; 
 int FUNCTABLE_SIZE ; 
 int M_PI ; 
 TYPE_5__ backEnd ; 
 TYPE_4__ tess ; 
 TYPE_3__ tr ; 

void RB_CalcBulgeVertexes( deformStage_t *ds ) {
	int i;
	const float *st = ( const float * ) tess.texCoords[0];
	float		*xyz = ( float * ) tess.xyz;
	float		*normal = ( float * ) tess.normal;
	double		now;

	now = backEnd.refdef.time * 0.001 * ds->bulgeSpeed;

	for ( i = 0; i < tess.numVertexes; i++, xyz += 4, st += 4, normal += 4 ) {
		int64_t off;
		float scale;

		off = (float)( FUNCTABLE_SIZE / (M_PI*2) ) * ( st[0] * ds->bulgeWidth + now );

		scale = tr.sinTable[ off & FUNCTABLE_MASK ] * ds->bulgeHeight;
			
		xyz[0] += normal[0] * scale;
		xyz[1] += normal[1] * scale;
		xyz[2] += normal[2] * scale;
	}
}