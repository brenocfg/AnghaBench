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
 scalar_t__ debug ; 
 int /*<<< orphan*/  mdname ; 
 int /*<<< orphan*/  path_mdconfig ; 
 int run (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_exitnumber (int) ; 
 int /*<<< orphan*/  run_exitstr (int) ; 
 int /*<<< orphan*/  unit ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_mdconfig_detach(void)
{
	int rv;

	rv = run(NULL, "%s -d -u %s%d", path_mdconfig, mdname, unit);
	if (rv && debug)	/* This is allowed to fail. */
		warnx("mdconfig (detach) exited %s %d (ignored)",
		    run_exitstr(rv), run_exitnumber(rv));
}