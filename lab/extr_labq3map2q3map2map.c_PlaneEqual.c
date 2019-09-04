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
typedef  scalar_t__* vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {scalar_t__ dist; scalar_t__* normal; } ;
typedef  TYPE_1__ plane_t ;

/* Variables and functions */
 float distanceEpsilon ; 
 float fabs (scalar_t__) ; 
 float normalEpsilon ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean PlaneEqual( plane_t *p, vec3_t normal, vec_t dist ){
	float ne, de;


	/* get local copies */
	ne = normalEpsilon;
	de = distanceEpsilon;

	/* compare */
	// We check equality of each component since we're using '<', not '<='
	// (the epsilons may be zero).  We want to use '<' intead of '<=' to be
	// consistent with the true meaning of "epsilon", and also because other
	// parts of the code uses this inequality.
	if ( ( p->dist == dist || fabs( p->dist - dist ) < de ) &&
		 ( p->normal[0] == normal[0] || fabs( p->normal[0] - normal[0] ) < ne ) &&
		 ( p->normal[1] == normal[1] || fabs( p->normal[1] - normal[1] ) < ne ) &&
		 ( p->normal[2] == normal[2] || fabs( p->normal[2] - normal[2] ) < ne ) ) {
		return qtrue;
	}

	/* different */
	return qfalse;
}