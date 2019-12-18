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
 scalar_t__ atf_utils_file_exists (char*) ; 
 int /*<<< orphan*/  system (char*) ; 

void
cleanup(void)
{
	if (atf_utils_file_exists("started_auditd"))
		system("service auditd onestop > /dev/null 2>&1");
}