#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ttyfd; scalar_t__ pid; int ptymaster; int /*<<< orphan*/  tty; TYPE_1__* pw; int /*<<< orphan*/  self; } ;
struct TYPE_4__ {int /*<<< orphan*/  pw_name; } ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  pty_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_logout (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void
session_pty_cleanup2(Session *s)
{
	if (s == NULL) {
		error("session_pty_cleanup: no session");
		return;
	}
	if (s->ttyfd == -1)
		return;

	debug("session_pty_cleanup: session %d release %s", s->self, s->tty);

	/* Record that the user has logged out. */
	if (s->pid != 0)
		record_logout(s->pid, s->tty, s->pw->pw_name);

	/* Release the pseudo-tty. */
	if (getuid() == 0)
		pty_release(s->tty);

	/*
	 * Close the server side of the socket pairs.  We must do this after
	 * the pty cleanup, so that another process doesn't get this pty
	 * while we're still cleaning up.
	 */
	if (s->ptymaster != -1 && close(s->ptymaster) < 0)
		error("close(s->ptymaster/%d): %s",
		    s->ptymaster, strerror(errno));

	/* unlink pty from session */
	s->ttyfd = -1;
}