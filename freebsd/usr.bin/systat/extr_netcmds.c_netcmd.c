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
 int /*<<< orphan*/  CMDLINE ; 
 int /*<<< orphan*/  addstr (char*) ; 
 int /*<<< orphan*/  changeitems (char const*,scalar_t__) ; 
 int /*<<< orphan*/  clrtoeol () ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  move (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ prefix (char const*,char*) ; 
 int /*<<< orphan*/  selecthost (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selectport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selectproto (char const*) ; 
 int /*<<< orphan*/  showhosts () ; 
 int /*<<< orphan*/  showports () ; 
 int /*<<< orphan*/  showprotos () ; 

int
netcmd(const char *cmd, const char *args)
{

	if (prefix(cmd, "proto")) {
		if (*args == '\0') {
			move(CMDLINE, 0);
			clrtoeol();
			addstr("which proto?");
		} else if (!selectproto(args)) {
			error("%s: Unknown protocol.", args);
		}
		return (1);
	}
	if (prefix(cmd, "ignore") || prefix(cmd, "display")) {
		changeitems(args, prefix(cmd, "display"));
		return (1);
	}
	if (prefix(cmd, "reset")) {
		selectproto(0);
		selecthost(0, 0);
		selectport(-1, 0);
		return (1);
	}
	if (prefix(cmd, "show")) {
		move(CMDLINE, 0); clrtoeol();
		if (*args == '\0') {
			showprotos();
			showhosts();
			showports();
			return (1);
		}
		if (prefix(args, "protos"))
			showprotos();
		else if (prefix(args, "hosts"))
			showhosts();
		else if (prefix(args, "ports"))
			showports();
		else
			addstr("show what?");
		return (1);
	}
	return (0);
}