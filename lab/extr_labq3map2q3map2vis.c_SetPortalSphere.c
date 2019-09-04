#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* origin; float radius; TYPE_2__* winding; } ;
typedef  TYPE_1__ vportal_t ;
typedef  int* vec3_t ;
struct TYPE_5__ {int numpoints; int /*<<< orphan*/ * points; } ;
typedef  TYPE_2__ fixedWinding_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorAdd (int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 float VectorLength (int*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int*,int*) ; 
 int* vec3_origin ; 

void SetPortalSphere( vportal_t *p ){
	int i;
	vec3_t total, dist;
	fixedWinding_t  *w;
	float r, bestr;

	w = p->winding;
	VectorCopy( vec3_origin, total );
	for ( i = 0 ; i < w->numpoints ; i++ )
	{
		VectorAdd( total, w->points[i], total );
	}

	for ( i = 0 ; i < 3 ; i++ )
		total[i] /= w->numpoints;

	bestr = 0;
	for ( i = 0 ; i < w->numpoints ; i++ )
	{
		VectorSubtract( w->points[i], total, dist );
		r = VectorLength( dist );
		if ( r > bestr ) {
			bestr = r;
		}
	}
	VectorCopy( total, p->origin );
	p->radius = bestr;
}