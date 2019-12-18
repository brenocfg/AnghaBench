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
struct winsize {unsigned short ws_row; unsigned short ws_col; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct winsize*) ; 

int generic_window_size(int fd, void *unused, unsigned short *rows_out,
			unsigned short *cols_out)
{
	struct winsize size;
	int ret;

	if (ioctl(fd, TIOCGWINSZ, &size) < 0)
		return -errno;

	ret = ((*rows_out != size.ws_row) || (*cols_out != size.ws_col));

	*rows_out = size.ws_row;
	*cols_out = size.ws_col;

	return ret;
}