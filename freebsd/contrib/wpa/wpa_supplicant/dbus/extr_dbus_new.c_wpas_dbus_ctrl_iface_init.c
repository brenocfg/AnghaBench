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
struct wpas_dbus_priv {int dbus_new_initialized; int /*<<< orphan*/  global; } ;
struct wpa_dbus_object_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_PATH ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_SERVICE ; 
 int /*<<< orphan*/  free_dbus_object_desc (struct wpa_dbus_object_desc*) ; 
 struct wpa_dbus_object_desc* os_zalloc (int) ; 
 int wpa_dbus_ctrl_iface_init (struct wpas_dbus_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_dbus_object_desc*) ; 
 int /*<<< orphan*/  wpa_dbus_ctrl_iface_props_deinit (struct wpas_dbus_priv*) ; 
 int wpa_dbus_ctrl_iface_props_init (struct wpas_dbus_priv*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpas_dbus_global_methods ; 
 int /*<<< orphan*/  wpas_dbus_global_properties ; 
 int /*<<< orphan*/  wpas_dbus_global_signals ; 
 int /*<<< orphan*/  wpas_dbus_register (struct wpa_dbus_object_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wpas_dbus_ctrl_iface_init(struct wpas_dbus_priv *priv)
{
	struct wpa_dbus_object_desc *obj_desc;
	int ret;

	ret = wpa_dbus_ctrl_iface_props_init(priv);
	if (ret < 0) {
		wpa_printf(MSG_ERROR,
			   "dbus: Not enough memory to init interface properties");
		return -1;
	}

	obj_desc = os_zalloc(sizeof(struct wpa_dbus_object_desc));
	if (!obj_desc) {
		wpa_printf(MSG_ERROR,
			   "Not enough memory to create object description");
		goto error;
	}

	wpas_dbus_register(obj_desc, priv->global, NULL,
			   wpas_dbus_global_methods,
			   wpas_dbus_global_properties,
			   wpas_dbus_global_signals);

	wpa_printf(MSG_DEBUG, "dbus: Register D-Bus object '%s'",
		   WPAS_DBUS_NEW_PATH);
	ret = wpa_dbus_ctrl_iface_init(priv, WPAS_DBUS_NEW_PATH,
				       WPAS_DBUS_NEW_SERVICE,
				       obj_desc);
	if (ret < 0) {
		free_dbus_object_desc(obj_desc);
		goto error;
	}

	priv->dbus_new_initialized = 1;
	return 0;

error:
	wpa_dbus_ctrl_iface_props_deinit(priv);
	return -1;
}