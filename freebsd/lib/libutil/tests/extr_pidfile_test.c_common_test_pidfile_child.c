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
struct kevent {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_SIGNAL ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int fork () ; 
 int kevent (int,struct kevent*,int,struct kevent*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ kill (int,int /*<<< orphan*/ ) ; 
 int kqueue () ; 
 int /*<<< orphan*/  pidfile_close (struct pidfh*) ; 
 struct pidfh* pidfile_open (char const*,int,int*) ; 
 scalar_t__ pidfile_write (struct pidfh*) ; 
 scalar_t__ pipe (int*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler ; 
 char const* strerror (int) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static const char *
common_test_pidfile_child(const char *fn, int parent_open)
{
	struct pidfh *pf = NULL;
	pid_t other = 0, pid = 0;
	int fd[2], serrno, status;
	struct kevent event, ke;
	char ch;
	int kq;

	unlink(fn);
	if (pipe(fd) != 0)
		return (strerror(errno));

	if (parent_open) {
		pf = pidfile_open(fn, 0600, &other);
		if (pf == NULL && other != 0)
			return ("pidfile exists and is locked");
		if (pf == NULL)
			return (strerror(errno));
	}

	pid = fork();
	if (pid == -1)
		return (strerror(errno));
	if (pid == 0) {
		// child
		close(fd[0]);
		signal(SIGINT, signal_handler);
		if (!parent_open) {
			pf = pidfile_open(fn, 0600, &other);
			if (pf == NULL && other != 0)
				return ("pidfile exists and is locked");
			if (pf == NULL)
				return (strerror(errno));
		}
		if (pidfile_write(pf) != 0) {
			serrno = errno;
			pidfile_close(pf);
			unlink(fn);
			return (strerror(serrno));
		}
		if (pf == NULL)
			_exit(1);
		if (pidfile_write(pf) != 0)
			_exit(2);
		kq = kqueue();
		if (kq == -1)
			_exit(3);
		EV_SET(&ke, SIGINT, EVFILT_SIGNAL, EV_ADD, 0, 0, NULL);
		/* Attach event to the kqueue. */
		if (kevent(kq, &ke, 1, NULL, 0, NULL) != 0)
			_exit(4);
		/* Inform the parent we are ready to receive SIGINT */
		if (write(fd[1], "*", 1) != 1)
			_exit(5);
		/* Wait for SIGINT received */
		if (kevent(kq, NULL, 0, &event, 1, NULL) != 1)
			_exit(6);
		_exit(0);
	}
	// parent
	close(fd[1]);
	if (pf)
		pidfile_close(pf);

	// wait for the child to signal us
	if (read(fd[0], &ch, 1) != 1) {
		serrno = errno;
		unlink(fn);
		kill(pid, SIGTERM);
		errno = serrno;
		return (strerror(errno));
	}

	// We shouldn't be able to lock the same pidfile as our child
	pf = pidfile_open(fn, 0600, &other);
	if (pf != NULL) {
		pidfile_close(pf);
		unlink(fn);
		return ("managed to lock contested pidfile");
	}

	// Failed to lock, but not because it was contested
	if (other == 0) {
		unlink(fn);
		return (strerror(errno));
	}

	// Locked by the wrong process
	if (other != pid) {
		unlink(fn);
		return ("pidfile contained wrong PID");
	}

	// check our child's fate
	if (pf)
		pidfile_close(pf);
	unlink(fn);
	if (kill(pid, SIGINT) != 0)
		return (strerror(errno));
	if (waitpid(pid, &status, 0) == -1)
		return (strerror(errno));
	if (WIFSIGNALED(status))
		return ("child caught signal");
	if (WEXITSTATUS(status) != 0) 
		return ("child returned non-zero status");

	// success
	return (NULL);
}