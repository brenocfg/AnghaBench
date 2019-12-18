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
 int /*<<< orphan*/  _PATH_MOUNT ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int run (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  run_exitnumber (int) ; 
 int /*<<< orphan*/  run_exitstr (int) ; 

__attribute__((used)) static void
do_mount_tmpfs(const char *args, const char *mtpoint)
{
	int rv;

	rv = run(NULL, "%s -t tmpfs %s tmp %s", _PATH_MOUNT, args, mtpoint);
	if (rv)
		errx(1, "tmpfs mount exited %s %d", run_exitstr(rv),
		    run_exitnumber(rv));
}