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
struct TYPE_2__ {int /*<<< orphan*/  (* DebugLineDelete ) (scalar_t__) ;} ;

/* Variables and functions */
 int MAX_DEBUGLINES ; 
 TYPE_1__ botimport ; 
 scalar_t__* debuglines ; 
 int /*<<< orphan*/ * debuglinevisible ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void AAS_ClearShownDebugLines(void)
{
	int i;

	//make all lines invisible
	for (i = 0; i < MAX_DEBUGLINES; i++)
	{
		if (debuglines[i])
		{
			//botimport.DebugLineShow(debuglines[i], NULL, NULL, LINECOLOR_NONE);
			botimport.DebugLineDelete(debuglines[i]);
			debuglines[i] = 0;
			debuglinevisible[i] = qfalse;
		} //end if
	} //end for
}