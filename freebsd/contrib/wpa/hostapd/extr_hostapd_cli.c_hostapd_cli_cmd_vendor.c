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
 int os_snprintf (char*,int,char*,char*,char*,char*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int wpa_ctrl_command (struct wpa_ctrl*,char*) ; 

__attribute__((used)) static int hostapd_cli_cmd_vendor(struct wpa_ctrl *ctrl, int argc, char *argv[])
{
	char cmd[256];
	int res;

	if (argc < 2 || argc > 3) {
		printf("Invalid vendor command\n"
		       "usage: <vendor id> <command id> [<hex formatted command argument>]\n");
		return -1;
	}

	res = os_snprintf(cmd, sizeof(cmd), "VENDOR %s %s %s", argv[0], argv[1],
			  argc == 3 ? argv[2] : "");
	if (os_snprintf_error(sizeof(cmd), res)) {
		printf("Too long VENDOR command.\n");
		return -1;
	}
	return wpa_ctrl_command(ctrl, cmd);
}