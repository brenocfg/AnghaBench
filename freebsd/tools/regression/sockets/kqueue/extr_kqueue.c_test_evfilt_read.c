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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct kevent {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_DELETE ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OK (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fail (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  fail_assertion (char*,char const*,char*,char*) ; 
 int kevent (int,struct kevent*,int,struct kevent*,int,struct timespec*) ; 
 int read (int,char*,int) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
test_evfilt_read(int kq, int fd[2], const char *socktype)
{
	struct timespec ts;
	struct kevent ke;
	ssize_t len;
	char ch;
	int i;

	EV_SET(&ke, fd[0], EVFILT_READ, EV_ADD, 0, 0, NULL);
	if (kevent(kq, &ke, 1, NULL, 0, NULL) == -1)
		fail(errno, "kevent", socktype, "EVFILT_READ, EV_ADD");
	OK("EVFILT_READ, EV_ADD");

	/*
	 * Confirm not readable to begin with, no I/O yet.
	 */
	ts.tv_sec = 0;
	ts.tv_nsec = 0;
	i = kevent(kq, NULL, 0, &ke, 1, &ts);
	if (i == -1)
		fail(errno, "kevent", socktype, "EVFILT_READ");
	OK("EVFILT_READ");
	if (i != 0)
		fail_assertion("kevent", socktype, "EVFILT_READ",
		    "empty socket unreadable");
	OK("empty socket unreadable");

	/*
	 * Write a byte to one end.
	 */
	ch = 'a';
	len = write(fd[1], &ch, sizeof(ch));
	if (len == -1)
		fail(errno, "write", socktype, NULL);
	OK("write one byte");
	if (len != sizeof(ch))
		fail_assertion("write", socktype, NULL, "write length");
	OK("write one byte length");

	/*
	 * Other end should now be readable.
	 */
	ts.tv_sec = 0;
	ts.tv_nsec = 0;
	i = kevent(kq, NULL, 0, &ke, 1, &ts);
	if (i == -1)
		fail(errno, "kevent", socktype, "EVFILT_READ");
	OK("EVFILT_READ");
	if (i != 1)
		fail_assertion("kevent", socktype, "EVFILT_READ",
		    "non-empty socket unreadable");
	OK("non-empty socket unreadable");

	/*
	 * Read a byte to clear the readable state.
	 */
	len = read(fd[0], &ch, sizeof(ch));
	if (len == -1)
		fail(errno, "read", socktype, NULL);
	OK("read one byte");
	if (len != sizeof(ch))
		fail_assertion("read", socktype, NULL, "read length");
	OK("read one byte length");

	/*
	 * Now re-check for readability.
	 */
	ts.tv_sec = 0;
	ts.tv_nsec = 0;
	i = kevent(kq, NULL, 0, &ke, 1, &ts);
	if (i == -1)
		fail(errno, "kevent", socktype, "EVFILT_READ");
	OK("EVFILT_READ");
	if (i != 0)
		fail_assertion("kevent", socktype, "EVFILT_READ",
		    "empty socket unreadable");
	OK("empty socket unreadable");

	EV_SET(&ke, fd[0], EVFILT_READ, EV_DELETE, 0, 0, NULL);
	if (kevent(kq, &ke, 1, NULL, 0, NULL) == -1)
		fail(errno, "kevent", socktype, "EVFILT_READ, EV_DELETE");
	OK("EVFILT_READ, EV_DELETE");
}