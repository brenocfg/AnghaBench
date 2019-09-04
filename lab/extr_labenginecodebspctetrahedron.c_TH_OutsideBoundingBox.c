#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_4__ {TYPE_1__* vertexes; } ;
struct TYPE_3__ {float* v; } ;

/* Variables and functions */
 TYPE_2__ thworld ; 

int TH_OutsideBoundingBox(int v1, int v2, vec3_t mins, vec3_t maxs)
{
	float *p1, *p2;
	int i;

	p1 = thworld.vertexes[v1].v;
	p2 = thworld.vertexes[v2].v;
	//if both points are at the outer side of one of the bounding box planes
	for (i = 0; i < 3; i++)
	{
		if (p1[i] < mins[i] && p2[i] < mins[i]) return true;
		if (p1[i] > maxs[i] && p2[i] > maxs[i]) return true;
	} //end for
	return false;
}