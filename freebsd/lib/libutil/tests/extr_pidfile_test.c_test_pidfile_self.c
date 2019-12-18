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
 int errno ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  pidfile_close (struct pidfh*) ; 
 struct pidfh* pidfile_open (char const*,int,scalar_t__*) ; 
 scalar_t__ pidfile_write (struct pidfh*) ; 
 char const* strerror (int) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

__attribute__((used)) static const char *
test_pidfile_self(void)
{
	const char *fn = "test_pidfile_self";
	struct pidfh *pf1, *pf2;
	pid_t other = 0;
	int serrno;

	unlink(fn);
	pf1 = pidfile_open(fn, 0600, &other);
	if (pf1 == NULL && other != 0)
		return ("pidfile exists and is locked");
	if (pf1 == NULL)
		return (strerror(errno));
	if (pidfile_write(pf1) != 0) {
		serrno = errno;
		pidfile_close(pf1);
		unlink(fn);
		return (strerror(serrno));
	}
	// second open should fail
	pf2 = pidfile_open(fn, 0600, &other);
	if (pf2 != NULL) {
		pidfile_close(pf1);
		pidfile_close(pf2);
		unlink(fn);
		return ("managed to opened pidfile twice");
	}
	if (other != getpid()) {
		pidfile_close(pf1);
		unlink(fn);
		return ("pidfile contained wrong PID");
	}
	pidfile_close(pf1);
	unlink(fn);
	return (NULL);
}