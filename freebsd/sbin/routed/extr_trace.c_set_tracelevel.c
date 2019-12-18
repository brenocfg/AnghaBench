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
 int /*<<< orphan*/ * ftrace ; 
 char* inittracename ; 
 scalar_t__ new_tracelevel ; 
 char* savetracename ; 
 int /*<<< orphan*/  set_tracefile (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigtrace_pat ; 
 scalar_t__ tracelevel ; 
 int /*<<< orphan*/  tracelevel_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
set_tracelevel(void)
{
	if (new_tracelevel == tracelevel)
		return;

	/* If tracing entirely off, and there was no tracefile specified
	 * on the command line, then leave it off.
	 */
	if (new_tracelevel > tracelevel && ftrace == NULL) {
		if (savetracename[0] != '\0') {
			set_tracefile(savetracename,sigtrace_pat,0);
		} else if (inittracename[0] != '\0') {
				set_tracefile(inittracename,sigtrace_pat,0);
		} else {
			new_tracelevel = 0;
			return;
		}
	} else {
		tracelevel_msg(sigtrace_pat, 0);
	}
}