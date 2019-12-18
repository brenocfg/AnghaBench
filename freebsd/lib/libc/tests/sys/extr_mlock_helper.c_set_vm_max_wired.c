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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAX_WIRED ; 
 int /*<<< orphan*/  atf_tc_skip (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_max_wired_sysctl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
set_vm_max_wired(u_long new_value)
{
	FILE *fp;
	u_long old_value;

	fp = fopen(VM_MAX_WIRED, "w");
	if (fp == NULL) {
		atf_tc_skip("could not open %s for writing: %s",
		    VM_MAX_WIRED, strerror(errno));
		return;
	}

	vm_max_wired_sysctl(&old_value, NULL);

	ATF_REQUIRE_MSG(fprintf(fp, "%lu", old_value) > 0,
	    "saving %s failed", VM_MAX_WIRED);

	fclose(fp);

	vm_max_wired_sysctl(NULL, &new_value);
}