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
 scalar_t__ EAGAIN ; 
 scalar_t__ ENOBUFS ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_DELETE ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OK (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fail (scalar_t__,char*,char const*,char*) ; 
 int /*<<< orphan*/  fail_assertion (char*,char const*,char*,char*) ; 
 int kevent (int,struct kevent*,int,struct kevent*,int,struct timespec*) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
test_evfilt_write(int kq, int fd[2], const char *socktype)
{
	struct timespec ts;
	struct kevent ke;
	ssize_t len;
	char ch;
	int i;

	EV_SET(&ke, fd[0], EVFILT_WRITE, EV_ADD, 0, 0, NULL);
	if (kevent(kq, &ke, 1, NULL, 0, NULL) == -1)
		fail(errno, "kevent", socktype, "EVFILT_WRITE, EV_ADD");
	OK("EVFILE_WRITE, EV_ADD");

	/*
	 * Confirm writable to begin with, no I/O yet.
	 */
	ts.tv_sec = 0;
	ts.tv_nsec = 0;
	i = kevent(kq, NULL, 0, &ke, 1, &ts);
	if (i == -1)
		fail(errno, "kevent", socktype, "EVFILT_WRITE");
	OK("EVFILE_WRITE");
	if (i != 1)
		fail_assertion("kevent", socktype, "EVFILT_WRITE",
		    "empty socket unwritable");
	OK("empty socket unwritable");

	/*
	 * Write bytes into the socket until we can't write anymore.
	 */
	ch = 'a';
	while ((len = write(fd[0], &ch, sizeof(ch))) == sizeof(ch)) {};
	if (len == -1 && errno != EAGAIN && errno != ENOBUFS)
		fail(errno, "write", socktype, NULL);
	OK("write");
	if (len != -1 && len != sizeof(ch))
		fail_assertion("write", socktype, NULL, "write length");
	OK("write length");

	/*
	 * Check to make sure the socket is no longer writable.
	 */
	ts.tv_sec = 0;
	ts.tv_nsec = 0;
	i = kevent(kq, NULL, 0, &ke, 1, &ts);
	if (i == -1)
		fail(errno, "kevent", socktype, "EVFILT_WRITE");
	OK("EVFILT_WRITE");
	if (i != 0)
		fail_assertion("kevent", socktype, "EVFILT_WRITE",
		    "full socket writable");
	OK("full socket writable");

	EV_SET(&ke, fd[0], EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
	if (kevent(kq, &ke, 1, NULL, 0, NULL) == -1)
		fail(errno, "kevent", socktype, "EVFILT_WRITE, EV_DELETE");
	OK("EVFILT_WRITE, EV_DELETE");
}