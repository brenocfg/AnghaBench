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
typedef  int u16 ;
struct wps_data {int dummy; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int ATTR_AUTH_TYPE_FLAGS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPS_AUTH_SHARED ; 
 int WPS_AUTH_TYPES ; 
 int WPS_AUTH_WPA ; 
 int WPS_AUTH_WPA2 ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int wps_force_auth_types ; 
 scalar_t__ wps_force_auth_types_in_use ; 

int wps_build_auth_type_flags(struct wps_data *wps, struct wpabuf *msg)
{
	u16 auth_types = WPS_AUTH_TYPES;
	/* WPA/WPA2-Enterprise enrollment not supported through WPS */
	auth_types &= ~WPS_AUTH_WPA;
	auth_types &= ~WPS_AUTH_WPA2;
	auth_types &= ~WPS_AUTH_SHARED;
#ifdef CONFIG_WPS_TESTING
	if (wps_force_auth_types_in_use) {
		wpa_printf(MSG_DEBUG,
			   "WPS: Testing - replace auth type 0x%x with 0x%x",
			   auth_types, wps_force_auth_types);
		auth_types = wps_force_auth_types;
	}
#endif /* CONFIG_WPS_TESTING */
	wpa_printf(MSG_DEBUG, "WPS:  * Authentication Type Flags (0x%x)",
		   auth_types);
	wpabuf_put_be16(msg, ATTR_AUTH_TYPE_FLAGS);
	wpabuf_put_be16(msg, 2);
	wpabuf_put_be16(msg, auth_types);
	return 0;
}