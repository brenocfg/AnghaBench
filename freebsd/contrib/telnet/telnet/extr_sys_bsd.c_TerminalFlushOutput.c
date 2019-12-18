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
 int /*<<< orphan*/  TCFLSH ; 
 int /*<<< orphan*/  TIOCFLUSH ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 

void
TerminalFlushOutput(void)
{
#ifdef	TIOCFLUSH
    (void) ioctl(fileno(stdout), TIOCFLUSH, (char *) 0);
#else
    (void) ioctl(fileno(stdout), TCFLSH, (char *) 0);
#endif
}