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
struct ctrl_iface_global_priv {scalar_t__ sock; int /*<<< orphan*/  ctrl_dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (scalar_t__) ; 
 int /*<<< orphan*/  os_free (struct ctrl_iface_global_priv*) ; 
 int /*<<< orphan*/  wpas_ctrl_iface_free_dst (int /*<<< orphan*/ ) ; 

void
wpa_supplicant_global_ctrl_iface_deinit(struct ctrl_iface_global_priv *priv)
{
	if (priv->sock >= 0) {
		eloop_unregister_read_sock(priv->sock);
		close(priv->sock);
	}

	wpas_ctrl_iface_free_dst(priv->ctrl_dst);
	os_free(priv);
}