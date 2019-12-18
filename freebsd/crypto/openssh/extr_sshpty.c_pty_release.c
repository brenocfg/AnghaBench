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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 scalar_t__ chmod (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ chown (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void
pty_release(const char *tty)
{
#if !defined(__APPLE_PRIVPTY__) && !defined(HAVE_OPENPTY)
	if (chown(tty, (uid_t) 0, (gid_t) 0) < 0)
		error("chown %.100s 0 0 failed: %.100s", tty, strerror(errno));
	if (chmod(tty, (mode_t) 0666) < 0)
		error("chmod %.100s 0666 failed: %.100s", tty, strerror(errno));
#endif /* !__APPLE_PRIVPTY__ && !HAVE_OPENPTY */
}