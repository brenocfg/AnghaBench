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
struct ctrl_iface_priv {int sock; scalar_t__ ctrl_dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (int) ; 
 int /*<<< orphan*/  os_free (struct ctrl_iface_priv*) ; 
 int /*<<< orphan*/  os_sleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_ctrl_iface_free_dst (scalar_t__) ; 

void wpa_supplicant_ctrl_iface_deinit(struct ctrl_iface_priv *priv)
{
	if (priv->sock > -1) {
		eloop_unregister_read_sock(priv->sock);
		if (priv->ctrl_dst) {
			/*
			 * Wait before closing the control socket if
			 * there are any attached monitors in order to allow
			 * them to receive any pending messages.
			 */
			wpa_printf(MSG_DEBUG, "CTRL_IFACE wait for attached "
				   "monitors to receive messages");
			os_sleep(0, 100000);
		}
		close(priv->sock);
		priv->sock = -1;
	}

	wpas_ctrl_iface_free_dst(priv->ctrl_dst);
	os_free(priv);
}