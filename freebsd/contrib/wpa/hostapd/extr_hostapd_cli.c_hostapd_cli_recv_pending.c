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
 int /*<<< orphan*/  cli_event (char*) ; 
 int /*<<< orphan*/ * ctrl_conn ; 
 int /*<<< orphan*/  hostapd_cli_action_process (char*,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ wpa_ctrl_pending (struct wpa_ctrl*) ; 
 scalar_t__ wpa_ctrl_recv (struct wpa_ctrl*,char*,size_t*) ; 

__attribute__((used)) static void hostapd_cli_recv_pending(struct wpa_ctrl *ctrl, int in_read,
				     int action_monitor)
{
	int first = 1;
	if (ctrl_conn == NULL)
		return;
	while (wpa_ctrl_pending(ctrl)) {
		char buf[4096];
		size_t len = sizeof(buf) - 1;
		if (wpa_ctrl_recv(ctrl, buf, &len) == 0) {
			buf[len] = '\0';
			if (action_monitor)
				hostapd_cli_action_process(buf, len);
			else {
				cli_event(buf);
				if (in_read && first)
					printf("\n");
				first = 0;
				printf("%s\n", buf);
			}
		} else {
			printf("Could not read pending message.\n");
			break;
		}
	}
}