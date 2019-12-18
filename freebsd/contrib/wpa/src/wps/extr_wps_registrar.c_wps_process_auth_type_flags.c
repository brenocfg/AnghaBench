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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wps_data {int auth_type; TYPE_1__* wps; } ;
struct TYPE_2__ {int auth_types; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int WPS_AUTH_WPA2 ; 
 int WPS_AUTH_WPA2PSK ; 
 int WPS_AUTH_WPAPSK ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_process_auth_type_flags(struct wps_data *wps, const u8 *auth)
{
	u16 auth_types;

	if (auth == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: No Authentication Type flags "
			   "received");
		return -1;
	}

	auth_types = WPA_GET_BE16(auth);

	wpa_printf(MSG_DEBUG, "WPS: Enrollee Authentication Type flags 0x%x",
		   auth_types);
#ifdef WPS_WORKAROUNDS
	/*
	 * Some deployed implementations seem to advertise incorrect information
	 * in this attribute. A value of 0x1b (WPA2 + WPA + WPAPSK + OPEN, but
	 * no WPA2PSK) has been reported to be used. Add WPA2PSK to the list to
	 * avoid issues with building Credentials that do not use the strongest
	 * actually supported authentication option (that device does support
	 * WPA2PSK even when it does not claim it here).
	 */
	if ((auth_types &
	     (WPS_AUTH_WPA2 | WPS_AUTH_WPA2PSK | WPS_AUTH_WPAPSK)) ==
	    (WPS_AUTH_WPA2 | WPS_AUTH_WPAPSK)) {
		wpa_printf(MSG_DEBUG,
			   "WPS: Workaround - assume Enrollee supports WPA2PSK based on claimed WPA2 support");
		auth_types |= WPS_AUTH_WPA2PSK;
	}
#endif /* WPS_WORKAROUNDS */
	wps->auth_type = wps->wps->auth_types & auth_types;
	if (wps->auth_type == 0) {
		wpa_printf(MSG_DEBUG, "WPS: No match in supported "
			   "authentication types (own 0x%x Enrollee 0x%x)",
			   wps->wps->auth_types, auth_types);
#ifdef WPS_WORKAROUNDS
		/*
		 * Some deployed implementations seem to advertise incorrect
		 * information in this attribute. For example, Linksys WRT350N
		 * seems to have a byteorder bug that breaks this negotiation.
		 * In order to interoperate with existing implementations,
		 * assume that the Enrollee supports everything we do.
		 */
		wpa_printf(MSG_DEBUG, "WPS: Workaround - assume Enrollee "
			   "does not advertise supported authentication types "
			   "correctly");
		wps->auth_type = wps->wps->auth_types;
#else /* WPS_WORKAROUNDS */
		return -1;
#endif /* WPS_WORKAROUNDS */
	}

	return 0;
}