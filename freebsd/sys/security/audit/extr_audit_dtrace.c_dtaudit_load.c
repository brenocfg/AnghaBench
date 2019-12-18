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
 int /*<<< orphan*/  DTRACE_PRIV_USER ; 
 int /*<<< orphan*/  dtaudit_attr ; 
 int /*<<< orphan*/  dtaudit_bsm ; 
 int /*<<< orphan*/  dtaudit_commit ; 
 int /*<<< orphan*/  dtaudit_hook_bsm ; 
 int /*<<< orphan*/  dtaudit_hook_commit ; 
 int /*<<< orphan*/  dtaudit_hook_preselect ; 
 int /*<<< orphan*/  dtaudit_id ; 
 int /*<<< orphan*/  dtaudit_pops ; 
 int /*<<< orphan*/  dtaudit_preselect ; 
 scalar_t__ dtrace_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtaudit_load(void *dummy)
{

	if (dtrace_register("audit", &dtaudit_attr, DTRACE_PRIV_USER, NULL,
	    &dtaudit_pops, NULL, &dtaudit_id) != 0)
		return;
	dtaudit_hook_preselect = dtaudit_preselect;
	dtaudit_hook_commit = dtaudit_commit;
	dtaudit_hook_bsm = dtaudit_bsm;
}