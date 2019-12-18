#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/  ltc; int /*<<< orphan*/  tc; int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCGETC ; 
 int /*<<< orphan*/  TIOCGETP ; 
 int /*<<< orphan*/  TIOCGLTC ; 
 int /*<<< orphan*/  TIOCGSTATE ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pty ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ termbuf ; 
 TYPE_1__ termbuf2 ; 

void
init_termbuf(void)
{
#ifndef	USE_TERMIO
	(void) ioctl(pty, TIOCGETP, (char *)&termbuf.sg);
	(void) ioctl(pty, TIOCGETC, (char *)&termbuf.tc);
	(void) ioctl(pty, TIOCGLTC, (char *)&termbuf.ltc);
# ifdef	TIOCGSTATE
	(void) ioctl(pty, TIOCGSTATE, (char *)&termbuf.state);
# endif
#else
	(void) tcgetattr(pty, &termbuf);
#endif
	termbuf2 = termbuf;
}