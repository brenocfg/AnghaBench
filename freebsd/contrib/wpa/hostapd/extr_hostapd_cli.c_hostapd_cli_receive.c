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
 int /*<<< orphan*/  ctrl_conn ; 
 int /*<<< orphan*/  hostapd_cli_recv_pending (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostapd_cli_receive(int sock, void *eloop_ctx, void *sock_ctx)
{
	hostapd_cli_recv_pending(ctrl_conn, 0, 0);
}