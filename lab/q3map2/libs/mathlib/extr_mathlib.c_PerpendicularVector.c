#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vec_t ;
typedef  float* vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  ProjectPointOnPlane (float*,float*,float* const) ; 
 int /*<<< orphan*/  VectorNormalize (float*,float*) ; 
 scalar_t__ fabs (float) ; 

void PerpendicularVector( vec3_t dst, const vec3_t src ){
	int pos;
	int i;
	vec_t minelem = 1.0F;
	vec3_t tempvec;

	/*
	** find the smallest magnitude axially aligned vector
	*/
	for ( pos = 0, i = 0; i < 3; i++ )
	{
		if ( fabs( src[i] ) < minelem ) {
			pos = i;
			minelem = (vec_t)fabs( src[i] );
		}
	}
	tempvec[0] = tempvec[1] = tempvec[2] = 0.0F;
	tempvec[pos] = 1.0F;

	/*
	** project the point onto the plane defined by src
	*/
	ProjectPointOnPlane( dst, tempvec, src );

	/*
	** normalize the result
	*/
	VectorNormalize( dst, dst );
}