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
 int /*<<< orphan*/  auditd_reap_children () ; 
 int close_all () ; 
 int close_misc () ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ launchd_flag ; 

void
auditd_terminate(void)
{
	int ret;

	auditd_reap_children();

	if (launchd_flag)
		ret = close_misc();
	else
		ret = close_all();

	exit(ret);
}