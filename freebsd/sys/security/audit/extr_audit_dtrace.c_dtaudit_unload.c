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
 int /*<<< orphan*/ * dtaudit_hook_bsm ; 
 int /*<<< orphan*/ * dtaudit_hook_commit ; 
 int /*<<< orphan*/ * dtaudit_hook_preselect ; 
 int /*<<< orphan*/  dtaudit_id ; 
 int dtrace_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtaudit_unload(void)
{
	int error;

	dtaudit_hook_preselect = NULL;
	dtaudit_hook_commit = NULL;
	dtaudit_hook_bsm = NULL;
	if ((error = dtrace_unregister(dtaudit_id)) != 0)
		return (error);
	return (0);
}