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
struct wps_parse_attr {int /*<<< orphan*/ * version2; int /*<<< orphan*/  response_type; int /*<<< orphan*/  version; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 
 scalar_t__ wps_validate_response_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_version (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_version2 (int /*<<< orphan*/ *,int) ; 

int wps_validate_assoc_resp(const struct wpabuf *wps_ie)
{
	struct wps_parse_attr attr;
	int wps2;

	if (wps_ie == NULL) {
		wpa_printf(MSG_INFO, "WPS-STRICT: No WPS IE in "
			   "(Re)Association Response frame");
		return -1;
	}
	if (wps_parse_msg(wps_ie, &attr) < 0) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Failed to parse WPS IE in "
			   "(Re)Association Response frame");
		return -1;
	}

	wps2 = attr.version2 != NULL;
	if (wps_validate_version(attr.version, 1) ||
	    wps_validate_response_type(attr.response_type, 1) ||
	    wps_validate_version2(attr.version2, wps2)) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid (Re)Association "
			   "Response frame");
		return -1;
	}

	return 0;
}