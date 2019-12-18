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
 int /*<<< orphan*/  STDIN_FILENO ; 
 scalar_t__ get_window_size (int /*<<< orphan*/ ,int*,int*) ; 

int
TerminalWindowSize(long *rows, long *cols)
{
    int irows, icols;

    if (get_window_size(STDIN_FILENO, &irows, &icols) == 0) {
	*rows = irows;
	*cols = icols;
	return 1;
    } else
	return 0;
}