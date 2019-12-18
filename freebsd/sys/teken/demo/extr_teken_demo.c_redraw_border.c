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
 unsigned int NCOLS ; 
 unsigned int NROWS ; 
 int /*<<< orphan*/  mvaddch (unsigned int,unsigned int,char) ; 

__attribute__((used)) static void
redraw_border(void)
{
	unsigned int i;

	for (i = 0; i < NROWS; i++)
		mvaddch(i, NCOLS, '|');
	for (i = 0; i < NCOLS; i++)
		mvaddch(NROWS, i, '-');

	mvaddch(NROWS, NCOLS, '+');
}