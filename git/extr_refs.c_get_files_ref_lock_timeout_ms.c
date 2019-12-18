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
 int /*<<< orphan*/  git_config_get_int (char*,int*) ; 

long get_files_ref_lock_timeout_ms(void)
{
	static int configured = 0;

	/* The default timeout is 100 ms: */
	static int timeout_ms = 100;

	if (!configured) {
		git_config_get_int("core.filesreflocktimeout", &timeout_ms);
		configured = 1;
	}

	return timeout_ms;
}