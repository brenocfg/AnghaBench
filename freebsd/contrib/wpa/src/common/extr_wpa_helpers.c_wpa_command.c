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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  wpa_ctrl_close (struct wpa_ctrl*) ; 
 scalar_t__ wpa_ctrl_request (struct wpa_ctrl*,char const*,int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *) ; 
 struct wpa_ctrl* wpa_open_ctrl (char const*) ; 

int wpa_command(const char *ifname, const char *cmd)
{
	struct wpa_ctrl *ctrl;
	char buf[128];
	size_t len;

	printf("wpa_command(ifname='%s', cmd='%s')\n", ifname, cmd);
	ctrl = wpa_open_ctrl(ifname);
	if (ctrl == NULL)
		return -1;
	len = sizeof(buf);
	if (wpa_ctrl_request(ctrl, cmd, strlen(cmd), buf, &len, NULL) < 0) {
		printf("wpa_command: wpa_ctrl_request failed\n");
		wpa_ctrl_close(ctrl);
		return -1;
	}
	wpa_ctrl_close(ctrl);
	buf[len] = '\0';
	if (strncmp(buf, "FAIL", 4) == 0) {
		printf("wpa_command: Command failed (FAIL received)\n");
		return -1;
	}
	return 0;
}