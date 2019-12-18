#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ws_col; } ;

/* Variables and functions */
 TYPE_1__* maxsize ; 
 int /*<<< orphan*/  tty_maxsize_update () ; 
 scalar_t__ use_dialog ; 
 scalar_t__ use_libdialog ; 
 scalar_t__ use_shadow ; 
 scalar_t__ use_xdialog ; 
 int /*<<< orphan*/  x11_maxsize_update () ; 

int
dialog_maxcols(void)
{

	if (use_xdialog && maxsize == NULL)
		x11_maxsize_update(); /* initialize maxsize for GUI */
	else if (!use_xdialog)
		tty_maxsize_update(); /* update maxsize for TTY */

	if (use_dialog || use_libdialog) {
		if (use_shadow)
			return (maxsize->ws_col - 2);
		else
			return (maxsize->ws_col);
	} else
		return (maxsize->ws_col);
}