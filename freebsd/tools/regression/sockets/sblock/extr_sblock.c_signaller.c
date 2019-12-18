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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int /*<<< orphan*/  SIGHUP ; 
 scalar_t__ close (int) ; 
 scalar_t__ kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int send (int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sleep (int) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static void
signaller(pid_t locking_recver_pid, int fd)
{
	ssize_t len;
	char ch;

	if (sleep(2) != 0) {
		warn("signaller sleep(2)");
		return;
	}
	if (kill(locking_recver_pid, SIGHUP) < 0) {
		warn("signaller kill(%d)", locking_recver_pid);
		return;
	}
	if (sleep(1) != 0) {
		warn("signaller sleep(1)");
		return;
	}
	len = send(fd, &ch, sizeof(ch), 0);
	if (len < 0) {
		warn("signaller send");
		return;
	}
	if (len != sizeof(ch)) {
		warnx("signaller send ret %zd", len);
		return;
	}
	if (close(fd) < 0) {
		warn("signaller close");
		return;
	}
	if (sleep(1) != 0) {
		warn("signaller sleep(1)");
		return;
	}
}