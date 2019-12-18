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

/* Variables and functions */
 int /*<<< orphan*/  SM_TIME_DEFAULT ; 
 int /*<<< orphan*/ * SmDebugOutput ; 
 int /*<<< orphan*/  sm_io_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * smioout ; 

void
sm_debug_close()
{
	if (SmDebugOutput != NULL && SmDebugOutput != smioout)
	{
		sm_io_close(SmDebugOutput, SM_TIME_DEFAULT);
		SmDebugOutput = NULL;
	}
}