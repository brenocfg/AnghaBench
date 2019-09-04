#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int qboolean ;
struct TYPE_2__ {int numplanes; } ;

/* Variables and functions */
 scalar_t__ AAS_PlaneEqual (int /*<<< orphan*/ ,float,int) ; 
 TYPE_1__ aasworld ; 

qboolean AAS_FindPlane(vec3_t normal, float dist, int *planenum)
{
	int i;

	for (i = 0; i < aasworld.numplanes; i++)
	{
		if (AAS_PlaneEqual(normal, dist, i))
		{
			*planenum = i;
			return true;
		} //end if
	} //end for
	return false;
}