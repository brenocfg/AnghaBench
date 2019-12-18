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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  wpa_ctrl_close (struct wpa_ctrl*) ; 
 scalar_t__ wpa_ctrl_request (struct wpa_ctrl*,char const*,int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *) ; 
 struct wpa_ctrl* wpa_open_ctrl (char const*) ; 

int wpa_command_resp(const char *ifname, const char *cmd,
		     char *resp, size_t resp_size)
{
	struct wpa_ctrl *ctrl;
	size_t len;

	printf("wpa_command(ifname='%s', cmd='%s')\n", ifname, cmd);
	ctrl = wpa_open_ctrl(ifname);
	if (ctrl == NULL)
		return -1;
	len = resp_size;
	if (wpa_ctrl_request(ctrl, cmd, strlen(cmd), resp, &len, NULL) < 0) {
		printf("wpa_command: wpa_ctrl_request failed\n");
		wpa_ctrl_close(ctrl);
		return -1;
	}
	wpa_ctrl_close(ctrl);
	resp[len] = '\0';
	return 0;
}