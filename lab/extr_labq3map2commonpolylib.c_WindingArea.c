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
struct TYPE_3__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  scalar_t__ vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vec_t   WindingArea( winding_t *w ){
	int i;
	vec3_t d1, d2, cross;
	vec_t total;

	total = 0;
	for ( i = 2 ; i < w->numpoints ; i++ )
	{
		VectorSubtract( w->p[i - 1], w->p[0], d1 );
		VectorSubtract( w->p[i], w->p[0], d2 );
		CrossProduct( d1, d2, cross );
		total += 0.5 * VectorLength( cross );
	}
	return total;
}