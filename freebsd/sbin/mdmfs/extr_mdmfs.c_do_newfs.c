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
 int /*<<< orphan*/  _PATH_NEWFS ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdname ; 
 int run (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_exitnumber (int) ; 
 int /*<<< orphan*/  run_exitstr (int) ; 
 int /*<<< orphan*/  unit ; 

__attribute__((used)) static void
do_newfs(const char *args)
{
	int rv;

	rv = run(NULL, "%s%s /dev/%s%d", _PATH_NEWFS, args, mdname, unit);
	if (rv)
		errx(1, "newfs exited %s %d", run_exitstr(rv),
		    run_exitnumber(rv));
}