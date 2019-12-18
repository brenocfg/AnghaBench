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
 scalar_t__ IsDebuggerPresent () ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  trace2_data_intmax (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void get_is_being_debugged(void)
{
	if (IsDebuggerPresent())
		trace2_data_intmax("process", the_repository,
				   "windows/debugger_present", 1);
}