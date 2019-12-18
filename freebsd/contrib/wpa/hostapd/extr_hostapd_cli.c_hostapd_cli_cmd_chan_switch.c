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
struct wpa_ctrl {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int os_snprintf (char*,int,char*,char*,...) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int wpa_ctrl_command (struct wpa_ctrl*,char*) ; 

__attribute__((used)) static int hostapd_cli_cmd_chan_switch(struct wpa_ctrl *ctrl,
				       int argc, char *argv[])
{
	char cmd[256];
	int res;
	int i;
	char *tmp;
	int total;

	if (argc < 2) {
		printf("Invalid chan_switch command: needs at least two "
		       "arguments (count and freq)\n"
		       "usage: <cs_count> <freq> [sec_channel_offset=] "
		       "[center_freq1=] [center_freq2=] [bandwidth=] "
		       "[blocktx] [ht|vht]\n");
		return -1;
	}

	res = os_snprintf(cmd, sizeof(cmd), "CHAN_SWITCH %s %s",
			  argv[0], argv[1]);
	if (os_snprintf_error(sizeof(cmd), res)) {
		printf("Too long CHAN_SWITCH command.\n");
		return -1;
	}

	total = res;
	for (i = 2; i < argc; i++) {
		tmp = cmd + total;
		res = os_snprintf(tmp, sizeof(cmd) - total, " %s", argv[i]);
		if (os_snprintf_error(sizeof(cmd) - total, res)) {
			printf("Too long CHAN_SWITCH command.\n");
			return -1;
		}
		total += res;
	}
	return wpa_ctrl_command(ctrl, cmd);
}