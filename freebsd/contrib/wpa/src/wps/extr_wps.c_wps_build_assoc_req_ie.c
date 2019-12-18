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
typedef  scalar_t__ u8 ;
struct wpabuf {int dummy; } ;
typedef  enum wps_request_type { ____Placeholder_wps_request_type } wps_request_type ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  WPS_DEV_OUI_WFA ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 
 scalar_t__* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_req_type (struct wpabuf*,int) ; 
 scalar_t__ wps_build_version (struct wpabuf*) ; 
 scalar_t__ wps_build_wfa_ext (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct wpabuf * wps_build_assoc_req_ie(enum wps_request_type req_type)
{
	struct wpabuf *ie;
	u8 *len;

	wpa_printf(MSG_DEBUG, "WPS: Building WPS IE for (Re)Association "
		   "Request");
	ie = wpabuf_alloc(100);
	if (ie == NULL)
		return NULL;

	wpabuf_put_u8(ie, WLAN_EID_VENDOR_SPECIFIC);
	len = wpabuf_put(ie, 1);
	wpabuf_put_be32(ie, WPS_DEV_OUI_WFA);

	if (wps_build_version(ie) ||
	    wps_build_req_type(ie, req_type) ||
	    wps_build_wfa_ext(ie, 0, NULL, 0, 0)) {
		wpabuf_free(ie);
		return NULL;
	}

	*len = wpabuf_len(ie) - 2;

	return ie;
}