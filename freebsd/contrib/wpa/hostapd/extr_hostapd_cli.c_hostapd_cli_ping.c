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
 scalar_t__ _wpa_ctrl_command (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ctrl_conn ; 
 int /*<<< orphan*/  ctrl_ifname ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*,void*),int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_cli_close_connection () ; 
 scalar_t__ hostapd_cli_reconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_cli_recv_pending (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ping_interval ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void hostapd_cli_ping(void *eloop_ctx, void *timeout_ctx)
{
	if (ctrl_conn && _wpa_ctrl_command(ctrl_conn, "PING", 0)) {
		printf("Connection to hostapd lost - trying to reconnect\n");
		hostapd_cli_close_connection();
	}
	if (!ctrl_conn && hostapd_cli_reconnect(ctrl_ifname) == 0)
		printf("Connection to hostapd re-established\n");
	if (ctrl_conn)
		hostapd_cli_recv_pending(ctrl_conn, 1, 0);
	eloop_register_timeout(ping_interval, 0, hostapd_cli_ping, NULL, NULL);
}