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
 int /*<<< orphan*/  action_file ; 
 int /*<<< orphan*/  ctrl_ifname ; 
 int /*<<< orphan*/  hostapd_cli_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 char* os_strchr (char const*,char) ; 

__attribute__((used)) static void hostapd_cli_action_process(char *msg, size_t len)
{
	const char *pos;

	pos = msg;
	if (*pos == '<') {
		pos = os_strchr(pos, '>');
		if (pos)
			pos++;
		else
			pos = msg;
	}

	hostapd_cli_exec(action_file, ctrl_ifname, pos);
}