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
 int /*<<< orphan*/ * ctrl_conn ; 
 scalar_t__ hostapd_cli_attached ; 
 int /*<<< orphan*/  unregister_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_ctrl_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_ctrl_detach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hostapd_cli_close_connection(void)
{
	if (ctrl_conn == NULL)
		return;

	unregister_event_handler(ctrl_conn);
	if (hostapd_cli_attached) {
		wpa_ctrl_detach(ctrl_conn);
		hostapd_cli_attached = 0;
	}
	wpa_ctrl_close(ctrl_conn);
	ctrl_conn = NULL;
}