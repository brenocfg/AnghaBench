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
 int /*<<< orphan*/  eloop_terminate () ; 
 int hostapd_cli_quit ; 
 scalar_t__ interactive ; 

__attribute__((used)) static int hostapd_cli_cmd_quit(struct wpa_ctrl *ctrl, int argc, char *argv[])
{
	hostapd_cli_quit = 1;
	if (interactive)
		eloop_terminate();
	return 0;
}