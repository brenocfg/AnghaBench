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
typedef  int /*<<< orphan*/  state_func_t ;
typedef  int /*<<< orphan*/  init_path ;

/* Variables and functions */
 int /*<<< orphan*/  KENV_GET ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  RB_REROOT ; 
 int /*<<< orphan*/  emergency (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execl (char*,char*,int /*<<< orphan*/ *) ; 
 int kenv (int /*<<< orphan*/ ,char*,char*,int) ; 
 int reboot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_user ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static state_func_t
reroot_phase_two(void)
{
	char init_path[PATH_MAX], *path, *path_component;
	size_t init_path_len;
	int nbytes, error;

	/*
	 * Ask the kernel to mount the new rootfs.
	 */
	error = reboot(RB_REROOT);
	if (error != 0) {
		emergency("RB_REBOOT failed: %s", strerror(errno));
		goto out;
	}

	/*
	 * Figure out where the destination init(8) binary is.  Note that
	 * the path could be different than what we've started with.  Use
	 * the value from kenv, if set, or the one from sysctl otherwise.
	 * The latter defaults to a hardcoded value, but can be overridden
	 * by a build time option.
	 */
	nbytes = kenv(KENV_GET, "init_path", init_path, sizeof(init_path));
	if (nbytes <= 0) {
		init_path_len = sizeof(init_path);
		error = sysctlbyname("kern.init_path",
		    init_path, &init_path_len, NULL, 0);
		if (error != 0) {
			emergency("failed to retrieve kern.init_path: %s",
			    strerror(errno));
			goto out;
		}
	}

	/*
	 * Repeat the init search logic from sys/kern/init_path.c
	 */
	path_component = init_path;
	while ((path = strsep(&path_component, ":")) != NULL) {
		/*
		 * Execute init(8) from the new rootfs.
		 */
		execl(path, path, NULL);
	}
	emergency("cannot exec init from %s: %s", init_path, strerror(errno));

out:
	emergency("reroot failed; going to single user mode");
	return (state_func_t) single_user;
}