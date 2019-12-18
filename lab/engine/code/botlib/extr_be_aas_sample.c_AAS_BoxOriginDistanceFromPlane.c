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
typedef  int /*<<< orphan*/  vec_t ;
typedef  scalar_t__* vec3_t ;

/* Variables and functions */
 scalar_t__ BBOX_NORMAL_EPSILON ; 
 int /*<<< orphan*/  DotProduct (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorInverse (scalar_t__*) ; 

vec_t AAS_BoxOriginDistanceFromPlane(vec3_t normal, vec3_t mins, vec3_t maxs, int side)
{
	vec3_t v1, v2;
	int i;

	//swap maxs and mins when on the other side of the plane
	if (side)
	{
		//get a point of the box that would be one of the first
		//to collide with the plane
		for (i = 0; i < 3; i++)
		{
			if (normal[i] > BBOX_NORMAL_EPSILON) v1[i] = maxs[i];
			else if (normal[i] < -BBOX_NORMAL_EPSILON) v1[i] = mins[i];
			else v1[i] = 0;
		} //end for
	} //end if
	else
	{
		//get a point of the box that would be one of the first
		//to collide with the plane
		for (i = 0; i < 3; i++)
		{
			if (normal[i] > BBOX_NORMAL_EPSILON) v1[i] = mins[i];
			else if (normal[i] < -BBOX_NORMAL_EPSILON) v1[i] = maxs[i];
			else v1[i] = 0;
		} //end for
	} //end else
	//
	VectorCopy(normal, v2);
	VectorInverse(v2);
//	VectorNegate(normal, v2);
	return DotProduct(v1, v2);
}