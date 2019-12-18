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
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_3__ {scalar_t__* normal; float dist; } ;
typedef  TYPE_1__ aas_plane_t ;

/* Variables and functions */
 float DotProduct (scalar_t__*,int /*<<< orphan*/ *) ; 

int AAS_BoxOnPlaneSide2(vec3_t absmins, vec3_t absmaxs, aas_plane_t *p)
{
	int i, sides;
	float dist1, dist2;
	vec3_t corners[2];

	for (i = 0; i < 3; i++)
	{
		if (p->normal[i] < 0)
		{
			corners[0][i] = absmins[i];
			corners[1][i] = absmaxs[i];
		} //end if
		else
		{
			corners[1][i] = absmins[i];
			corners[0][i] = absmaxs[i];
		} //end else
	} //end for
	dist1 = DotProduct(p->normal, corners[0]) - p->dist;
	dist2 = DotProduct(p->normal, corners[1]) - p->dist;
	sides = 0;
	if (dist1 >= 0) sides = 1;
	if (dist2 < 0) sides |= 2;

	return sides;
}