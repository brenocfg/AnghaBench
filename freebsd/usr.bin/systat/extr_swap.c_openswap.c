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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int LINES ; 
 int /*<<< orphan*/  MAINWIN_ROW ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/ * subwin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

WINDOW *
openswap(void)
{
	return (subwin(stdscr, LINES-3-1, 0, MAINWIN_ROW, 0));
}