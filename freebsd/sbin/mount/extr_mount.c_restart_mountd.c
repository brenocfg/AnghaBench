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
struct pidfh {int dummy; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  _PATH_MOUNTDPID ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int kill (scalar_t__,int /*<<< orphan*/ ) ; 
 struct pidfh* pidfile_open (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  pidfile_remove (struct pidfh*) ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__) ; 

__attribute__((used)) static void
restart_mountd(void)
{
	struct pidfh *pfh;
	pid_t mountdpid;

	mountdpid = 0;
	pfh = pidfile_open(_PATH_MOUNTDPID, 0600, &mountdpid);
	if (pfh != NULL) {
		/* Mountd is not running. */
		pidfile_remove(pfh);
		return;
	}
	if (errno != EEXIST) {
		/* Cannot open pidfile for some reason. */
		return;
	}

	/*
	 * Refuse to send broadcast or group signals, this has
	 * happened due to the bugs in pidfile(3).
	 */
	if (mountdpid <= 0) {
		warnx("mountd pid %d, refusing to send SIGHUP", mountdpid);
		return;
	}

	/* We have mountd(8) PID in mountdpid varible, let's signal it. */
	if (kill(mountdpid, SIGHUP) == -1)
		err(1, "signal mountd");
}