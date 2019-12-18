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
 int /*<<< orphan*/  ctrl_conn ; 
 int /*<<< orphan*/  eloop_register_read_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int event_handler_registered ; 
 int /*<<< orphan*/  hostapd_cli_receive ; 
 scalar_t__ interactive ; 
 int /*<<< orphan*/  wpa_ctrl_get_fd (struct wpa_ctrl*) ; 

__attribute__((used)) static void register_event_handler(struct wpa_ctrl *ctrl)
{
	if (!ctrl_conn)
		return;
	if (interactive) {
		event_handler_registered =
			!eloop_register_read_sock(wpa_ctrl_get_fd(ctrl),
						  hostapd_cli_receive,
						  NULL, NULL);
	}
}