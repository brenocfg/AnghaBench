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
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  check_local () ; 
 int /*<<< orphan*/  check_writeable () ; 
 int /*<<< orphan*/  end_msgs () ; 
 int /*<<< orphan*/  get_names (int,char**) ; 
 int /*<<< orphan*/  init_display () ; 
 int /*<<< orphan*/  invite_remote () ; 
 int /*<<< orphan*/  open_ctl () ; 
 int /*<<< orphan*/  open_sockt () ; 
 int /*<<< orphan*/  set_edit_chars () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setproctitle (char*) ; 
 int /*<<< orphan*/  start_msgs () ; 
 int /*<<< orphan*/  talk () ; 

int
main(int argc, char **argv)
{
	(void) setlocale(LC_CTYPE, "");

	get_names(argc, argv);
	setproctitle(" ");
	check_writeable();
	init_display();
	open_ctl();
	open_sockt();
	start_msgs();
	if (!check_local())
		invite_remote();
	end_msgs();
	set_edit_chars();
	talk();
	return 0;
}