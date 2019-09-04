#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_3__ {int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ plane_t ;

/* Variables and functions */
 scalar_t__ DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * baseaxis ; 

void TextureAxisFromPlane( plane_t *pln, vec3_t xv, vec3_t yv ){
	int bestaxis;
	vec_t dot,best;
	int i;

	best = 0;
	bestaxis = 0;

	for ( i = 0 ; i < 6 ; i++ )
	{
		dot = DotProduct( pln->normal, baseaxis[i * 3] );
		if ( dot > best + 0.0001f ) { /* ydnar: bug 637 fix, suggested by jmonroe */
			best = dot;
			bestaxis = i;
		}
	}

	VectorCopy( baseaxis[bestaxis * 3 + 1], xv );
	VectorCopy( baseaxis[bestaxis * 3 + 2], yv );
}