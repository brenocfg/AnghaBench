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
struct TYPE_2__ {int /*<<< orphan*/  (* DebugPolygonDelete ) (scalar_t__) ;} ;

/* Variables and functions */
 int MAX_DEBUGPOLYGONS ; 
 TYPE_1__ botimport ; 
 scalar_t__* debugpolygons ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void AAS_ClearShownPolygons(void)
{
	int i;
//*
	for (i = 0; i < MAX_DEBUGPOLYGONS; i++)
	{
		if (debugpolygons[i]) botimport.DebugPolygonDelete(debugpolygons[i]);
		debugpolygons[i] = 0;
	} //end for
//*/
/*
	for (i = 0; i < MAX_DEBUGPOLYGONS; i++)
	{
		botimport.DebugPolygonDelete(i);
		debugpolygons[i] = 0;
	} //end for
*/
}