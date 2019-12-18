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
struct TYPE_2__ {int /*<<< orphan*/ * ctrl_interface; } ;
struct wpa_global {TYPE_1__ params; } ;
struct ctrl_iface_global_priv {int sock; struct wpa_global* global; int /*<<< orphan*/  msg_queue; int /*<<< orphan*/  ctrl_dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct ctrl_iface_global_priv*) ; 
 struct ctrl_iface_global_priv* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_msg_register_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_ctrl_iface_msg_cb ; 
 scalar_t__ wpas_global_ctrl_iface_open_sock (struct wpa_global*,struct ctrl_iface_global_priv*) ; 

struct ctrl_iface_global_priv *
wpa_supplicant_global_ctrl_iface_init(struct wpa_global *global)
{
	struct ctrl_iface_global_priv *priv;

	priv = os_zalloc(sizeof(*priv));
	if (priv == NULL)
		return NULL;
	dl_list_init(&priv->ctrl_dst);
	dl_list_init(&priv->msg_queue);
	priv->global = global;
	priv->sock = -1;

	if (global->params.ctrl_interface == NULL)
		return priv;

	if (wpas_global_ctrl_iface_open_sock(global, priv) < 0) {
		os_free(priv);
		return NULL;
	}

	wpa_msg_register_cb(wpa_supplicant_ctrl_iface_msg_cb);

	return priv;
}