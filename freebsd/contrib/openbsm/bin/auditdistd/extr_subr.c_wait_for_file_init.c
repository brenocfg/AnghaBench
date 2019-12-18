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
struct kevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EVFILT_VNODE ; 
 int EV_ADD ; 
 int EV_CLEAR ; 
 int EV_ENABLE ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  NOTE_RENAME ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int kevent (int,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kqueue () ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 
 int wait_for_file_kq ; 

int
wait_for_file_init(int fd)
{
#ifdef HAVE_KQUEUE
	struct kevent ev[2];
	int error, kq;
#endif

	PJDLOG_ASSERT(fd != -1);

#ifdef HAVE_KQUEUE
	if (wait_for_file_kq != -1) {
		close(wait_for_file_kq);
		wait_for_file_kq = -1;
	}

	kq = kqueue();
	if (kq == -1) {
		pjdlog_errno(LOG_WARNING, "kqueue() failed");
		return (-1);
	}
	EV_SET(&ev[0], fd, EVFILT_VNODE, EV_ADD | EV_ENABLE | EV_CLEAR,
	    NOTE_RENAME, 0, 0);
	EV_SET(&ev[1], fd, EVFILT_READ, EV_ADD | EV_ENABLE | EV_CLEAR,
	    0, 0, 0);
	if (kevent(kq, ev, 2, NULL, 0, NULL) == -1) {
		error = errno;
		pjdlog_errno(LOG_WARNING, "kevent() failed");
		(void)close(kq);
		errno = error;
		return (-1);
	}
	wait_for_file_kq = kq;
#endif

	return (0);
}