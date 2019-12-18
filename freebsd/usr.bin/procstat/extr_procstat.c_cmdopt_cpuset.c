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
 int /*<<< orphan*/  PS_OPT_PERTHREAD ; 
 int /*<<< orphan*/  cmdopt_none (int,char* const*) ; 
 int /*<<< orphan*/  procstat_opts ; 

void
cmdopt_cpuset(int argc, char * const argv[])
{

	procstat_opts |= PS_OPT_PERTHREAD;
	cmdopt_none(argc, argv);
}