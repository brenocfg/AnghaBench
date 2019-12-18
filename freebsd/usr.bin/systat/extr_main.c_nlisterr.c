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
struct nlist {char* n_name; scalar_t__ n_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDLINE ; 
 int /*<<< orphan*/  clear () ; 
 int /*<<< orphan*/  clrtoeol () ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  move (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvprintw (int,int,char*,...) ; 
 int /*<<< orphan*/  refresh () ; 

void
nlisterr(struct nlist n_list[])
{
	int i, n;

	n = 0;
	clear();
	mvprintw(2, 10, "systat: nlist: can't find following symbols:");
	for (i = 0;
	    n_list[i].n_name != NULL && *n_list[i].n_name != '\0'; i++)
		if (n_list[i].n_value == 0)
			mvprintw(2 + ++n, 10, "%s", n_list[i].n_name);
	move(CMDLINE, 0);
	clrtoeol();
	refresh();
	endwin();
	exit(1);
}