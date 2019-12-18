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

/* Variables and functions */
 scalar_t__ ESRCH ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  _PATH_REROOT ; 
 int /*<<< orphan*/  _PATH_REROOT_INIT ; 
 int create_file (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  emergency (char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  init_path_argv0 ; 
 int kill (int,int /*<<< orphan*/ ) ; 
 int mount_tmpfs (int /*<<< orphan*/ ) ; 
 int read_file (int /*<<< orphan*/ ,void**,size_t*) ; 
 int /*<<< orphan*/  revoke_ttys () ; 
 int /*<<< orphan*/  runshutdown () ; 
 int /*<<< orphan*/  single_user ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static state_func_t
reroot(void)
{
	void *buf;
	size_t bufsize;
	int error;

	buf = NULL;
	bufsize = 0;

	revoke_ttys();
	runshutdown();

	/*
	 * Make sure nobody can interfere with our scheme.
	 * Ignore ESRCH, which can apparently happen when
	 * there are no processes to kill.
	 */
	error = kill(-1, SIGKILL);
	if (error != 0 && errno != ESRCH) {
		emergency("kill(2) failed: %s", strerror(errno));
		goto out;
	}

	/*
	 * Copy the init binary into tmpfs, so that we can unmount
	 * the old rootfs without committing suicide.
	 */
	error = read_file(init_path_argv0, &buf, &bufsize);
	if (error != 0)
		goto out;
	error = mount_tmpfs(_PATH_REROOT);
	if (error != 0)
		goto out;
	error = create_file(_PATH_REROOT_INIT, buf, bufsize);
	if (error != 0)
		goto out;

	/*
	 * Execute the temporary init.
	 */
	execl(_PATH_REROOT_INIT, _PATH_REROOT_INIT, "-r", NULL);
	emergency("cannot exec %s: %s", _PATH_REROOT_INIT, strerror(errno));

out:
	emergency("reroot failed; going to single user mode");
	free(buf);
	return (state_func_t) single_user;
}