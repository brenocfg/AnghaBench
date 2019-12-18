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
struct winsize {int ws_col; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 int tgetnum (char*) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static int
ttywidth(void)
{
	struct winsize ws;
	int width;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1)
		width = ws.ws_col;
	else if ((width = tgetnum("co")) == 0) {
		width = 80;
		warnx("cannot find terminal width; defaulted to %d", width);
	}

	return (width);
}