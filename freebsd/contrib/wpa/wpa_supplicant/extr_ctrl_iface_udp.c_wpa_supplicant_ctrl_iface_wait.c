#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ctrl_iface_priv {int /*<<< orphan*/  sock; TYPE_1__* wpa_s; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_wait_for_read_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void wpa_supplicant_ctrl_iface_wait(struct ctrl_iface_priv *priv)
{
	wpa_printf(MSG_DEBUG, "CTRL_IFACE - %s - wait for monitor",
		   priv->wpa_s->ifname);
	eloop_wait_for_read_sock(priv->sock);
}