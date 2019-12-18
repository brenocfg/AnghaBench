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
struct wps_context {int ap_setup_locked; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int ATTR_AP_SETUP_LOCKED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static int wps_build_ap_setup_locked(struct wps_context *wps,
				     struct wpabuf *msg)
{
	if (wps->ap_setup_locked && wps->ap_setup_locked != 2) {
		wpa_printf(MSG_DEBUG, "WPS:  * AP Setup Locked");
		wpabuf_put_be16(msg, ATTR_AP_SETUP_LOCKED);
		wpabuf_put_be16(msg, 1);
		wpabuf_put_u8(msg, 1);
	}
	return 0;
}