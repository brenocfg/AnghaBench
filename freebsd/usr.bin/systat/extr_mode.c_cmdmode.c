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
struct TYPE_2__ {int /*<<< orphan*/  (* c_reset ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CMDLINE ; 
 int /*<<< orphan*/  clrtoeol () ; 
 TYPE_1__* curcmd ; 
 size_t currentmode ; 
 size_t display_ABS ; 
 size_t display_DELTA ; 
 size_t display_RATE ; 
 size_t display_SINCE ; 
 char const** modes ; 
 int /*<<< orphan*/  move (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ prefix (char const*,char*) ; 
 int /*<<< orphan*/  printw (char*,char const*) ; 
 int /*<<< orphan*/  stub1 () ; 

int
cmdmode(const char *cmd, const char *args)
{
	if (prefix(cmd, "mode")) {
		if (args[0] == '\0') {
			move(CMDLINE, 0);
			clrtoeol();
			printw("%s", modes[currentmode]);
		} else if (prefix(args, "rate")) {
			currentmode = display_RATE;
		} else if (prefix(args, "delta")) {
			currentmode = display_DELTA;
		} else if (prefix(args, "since")) {
			currentmode = display_SINCE;
		} else if (prefix(args, "absolute")) {
			currentmode = display_ABS;
		} else {
			printw("unknown mode `%s'", args);
		}
		return 1;
	}
	if(prefix(cmd, "reset")) {
		curcmd->c_reset();
		return 1;
	}
	return 0;
}