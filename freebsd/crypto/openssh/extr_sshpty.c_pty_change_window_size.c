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
typedef  void* u_int ;
struct winsize {void* ws_ypixel; void* ws_xpixel; void* ws_col; void* ws_row; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCSWINSZ ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,struct winsize*) ; 

void
pty_change_window_size(int ptyfd, u_int row, u_int col,
	u_int xpixel, u_int ypixel)
{
	struct winsize w;

	/* may truncate u_int -> u_short */
	w.ws_row = row;
	w.ws_col = col;
	w.ws_xpixel = xpixel;
	w.ws_ypixel = ypixel;
	(void) ioctl(ptyfd, TIOCSWINSZ, &w);
}