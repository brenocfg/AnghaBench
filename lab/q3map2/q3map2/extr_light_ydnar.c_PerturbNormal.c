#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec4_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_7__ {TYPE_1__* normalImage; } ;
typedef  TYPE_2__ shaderInfo_t ;
struct TYPE_8__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  st; } ;
typedef  TYPE_3__ bspDrawVert_t ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixels; } ;

/* Variables and functions */
 scalar_t__ RadSampleImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qfalse ; 

__attribute__((used)) static void PerturbNormal( bspDrawVert_t *dv, shaderInfo_t *si, vec3_t pNormal, vec3_t stv[ 3 ], vec3_t ttv[ 3 ] ){
	int i;
	vec4_t bump;


	/* passthrough */
	VectorCopy( dv->normal, pNormal );

	/* sample normalmap */
	if ( RadSampleImage( si->normalImage->pixels, si->normalImage->width, si->normalImage->height, dv->st, bump ) == qfalse ) {
		return;
	}

	/* remap sampled normal from [0,255] to [-1,-1] */
	for ( i = 0; i < 3; i++ )
		bump[ i ] = ( bump[ i ] - 127.0f ) * ( 1.0f / 127.5f );

	/* scale tangent vectors and add to original normal */
	VectorMA( dv->normal, bump[ 0 ], stv[ 0 ], pNormal );
	VectorMA( pNormal, bump[ 1 ], ttv[ 0 ], pNormal );
	VectorMA( pNormal, bump[ 2 ], dv->normal, pNormal );

	/* renormalize and return */
	VectorNormalize( pNormal, pNormal );
}