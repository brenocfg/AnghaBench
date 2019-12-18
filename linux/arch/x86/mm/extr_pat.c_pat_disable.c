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
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ boot_cpu_done ; 
 int pat_disabled ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 

void pat_disable(const char *reason)
{
	if (pat_disabled)
		return;

	if (boot_cpu_done) {
		WARN_ONCE(1, "x86/PAT: PAT cannot be disabled after initialization\n");
		return;
	}

	pat_disabled = true;
	pr_info("x86/PAT: %s\n", reason);
}