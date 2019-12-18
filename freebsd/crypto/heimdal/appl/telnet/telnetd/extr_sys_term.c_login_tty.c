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

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  TIOCSCTTY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  fatalperror (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char*) ; 
 char* line ; 
 int /*<<< orphan*/  net ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  really_stream ; 
 int /*<<< orphan*/  setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpgrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int login_tty(int t)
{
    /* Dont need to set this as the controlling PTY on steams sockets,
     * don't abort on failure. */
# if defined(TIOCSCTTY) && !defined(__hpux)
    if (ioctl(t, TIOCSCTTY, (char *)0) < 0 && !really_stream)
	fatalperror(net, "ioctl(sctty)");
#  ifdef _CRAY
    /*
     * Close the hard fd to /dev/ttypXXX, and re-open through
     * the indirect /dev/tty interface.
     */
    close(t);
    if ((t = open("/dev/tty", O_RDWR)) < 0)
	fatalperror(net, "open(/dev/tty)");
#  endif
# else
    /*
     * We get our controlling tty assigned as a side-effect
     * of opening up a tty device.  But on BSD based systems,
     * this only happens if our process group is zero.  The
     * setsid() call above may have set our pgrp, so clear
     * it out before opening the tty...
     */
#ifdef HAVE_SETPGID
    setpgid(0, 0);
#else
    setpgrp(0, 0); /* if setpgid isn't available, setpgrp
		      probably takes arguments */
#endif
    close(open(line, O_RDWR));
# endif
    if (t != 0)
	dup2(t, 0);
    if (t != 1)
	dup2(t, 1);
    if (t != 2)
	dup2(t, 2);
    if (t > 2)
	close(t);
    return(0);
}