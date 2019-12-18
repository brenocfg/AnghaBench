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
typedef  int /*<<< orphan*/  heim_sipc ;

/* Variables and functions */
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 int /*<<< orphan*/  heim_ipc_main () ; 
 int /*<<< orphan*/  heim_sipc_launchd_mach_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heim_sipc_service_unix (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ help_flag ; 
 int /*<<< orphan*/  num_args ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  test_service ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ version_flag ; 

int
main(int argc, char **argv)
{
    heim_sipc u;
    int optidx = 0;

    setprogname(argv[0]);

    if (getarg(args, num_args, argc, argv, &optidx))
	usage(1);

    if (help_flag)
	usage(0);

    if (version_flag) {
	print_version(NULL);
	exit(0);
    }

#if __APPLE__
    {
	heim_sipc mach;
	heim_sipc_launchd_mach_init("org.h5l.test-ipc",
				    test_service, NULL, &mach);
    }
#endif
    heim_sipc_service_unix("org.h5l.test-ipc",
			   test_service, NULL, &u);
    heim_ipc_main();

    return 0;
}