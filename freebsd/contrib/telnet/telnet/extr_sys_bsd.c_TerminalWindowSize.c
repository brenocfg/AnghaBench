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
struct winsize {long ws_row; long ws_col; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdin ; 

int
TerminalWindowSize(long *rows, long *cols)
{
#ifdef	TIOCGWINSZ
    struct winsize ws;

    if (ioctl(fileno(stdin), TIOCGWINSZ, (char *)&ws) >= 0) {
	*rows = ws.ws_row;
	*cols = ws.ws_col;
	return 1;
    }
#endif	/* TIOCGWINSZ */
    return 0;
}