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
struct TYPE_3__ {int /*<<< orphan*/  debug_level; struct TYPE_3__* debug_next; } ;
typedef  TYPE_1__ SM_DEBUG_T ;

/* Variables and functions */
 int /*<<< orphan*/  SM_DEBUG_UNKNOWN ; 
 TYPE_1__* SmDebugInitialized ; 

__attribute__((used)) static void
sm_debug_reset()
{
	SM_DEBUG_T *debug;

	for (debug = SmDebugInitialized;
	     debug != NULL;
	     debug = debug->debug_next)
	{
		debug->debug_level = SM_DEBUG_UNKNOWN;
	}
	SmDebugInitialized = NULL;
}