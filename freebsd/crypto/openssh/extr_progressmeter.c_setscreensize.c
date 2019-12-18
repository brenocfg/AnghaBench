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
struct winsize {scalar_t__ ws_col; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_WINSIZE ; 
 scalar_t__ MAX_WINSIZE ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 scalar_t__ win_size ; 

__attribute__((used)) static void
setscreensize(void)
{
	struct winsize winsize;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsize) != -1 &&
	    winsize.ws_col != 0) {
		if (winsize.ws_col > MAX_WINSIZE)
			win_size = MAX_WINSIZE;
		else
			win_size = winsize.ws_col;
	} else
		win_size = DEFAULT_WINSIZE;
	win_size += 1;					/* trailing \0 */
}