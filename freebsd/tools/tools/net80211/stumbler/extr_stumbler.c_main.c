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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cbreak () ; 
 int /*<<< orphan*/  cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear () ; 
 int /*<<< orphan*/  curs_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  init_globals () ; 
 int /*<<< orphan*/  initscr () ; 
 int /*<<< orphan*/  intrflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  nonl () ; 
 int /*<<< orphan*/  own (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  stdscr ; 

int main(int argc, char *argv[]) {


	if (argc < 2) {
		printf("Usage: %s <iface>\n", argv[0]);
		exit(1);
	}

	init_globals();

	initscr(); cbreak(); noecho();
	
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	curs_set(0);

	clear();
	refresh();

	signal(SIGINT, cleanup);
	signal(SIGTERM, cleanup);
	
	own(argv[1]);

	cleanup(0);
	exit(0);
}