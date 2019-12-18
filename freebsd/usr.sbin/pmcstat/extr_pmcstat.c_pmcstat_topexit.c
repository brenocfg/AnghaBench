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
struct TYPE_2__ {int /*<<< orphan*/  pa_toptty; } ;

/* Variables and functions */
 TYPE_1__ args ; 
 int /*<<< orphan*/  clrtoeol () ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  refresh () ; 

void
pmcstat_topexit(void)
{
	if (!args.pa_toptty)
		return;

	/*
	 * Shutdown ncurses.
	 */
	clrtoeol();
	refresh();
	endwin();
}