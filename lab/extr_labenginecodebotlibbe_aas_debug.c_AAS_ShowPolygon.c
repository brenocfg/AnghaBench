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
struct TYPE_2__ {scalar_t__ (* DebugPolygonCreate ) (int,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int MAX_DEBUGPOLYGONS ; 
 TYPE_1__ botimport ; 
 scalar_t__* debugpolygons ; 
 scalar_t__ stub1 (int,int,int /*<<< orphan*/ *) ; 

void AAS_ShowPolygon(int color, int numpoints, vec3_t *points)
{
	int i;

	for (i = 0; i < MAX_DEBUGPOLYGONS; i++)
	{
		if (!debugpolygons[i])
		{
			debugpolygons[i] = botimport.DebugPolygonCreate(color, numpoints, points);
			break;
		} //end if
	} //end for
}