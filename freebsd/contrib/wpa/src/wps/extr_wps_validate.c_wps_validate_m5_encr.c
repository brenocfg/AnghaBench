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
struct wps_parse_attr {int /*<<< orphan*/  key_wrap_auth; int /*<<< orphan*/  e_snonce1; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 
 scalar_t__ wps_validate_e_snonce1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_key_wrap_auth (int /*<<< orphan*/ ,int) ; 

int wps_validate_m5_encr(const struct wpabuf *tlvs, int wps2)
{
	struct wps_parse_attr attr;

	if (tlvs == NULL) {
		wpa_printf(MSG_INFO, "WPS-STRICT: No TLVs in M5 encrypted "
			   "settings");
		return -1;
	}
	if (wps_parse_msg(tlvs, &attr) < 0) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Failed to parse attributes "
			   "in M5 encrypted settings");
		return -1;
	}

	if (wps_validate_e_snonce1(attr.e_snonce1, 1) ||
	    wps_validate_key_wrap_auth(attr.key_wrap_auth, 1)) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid M5 encrypted "
			   "settings");
#ifdef WPS_STRICT_WPS2
		if (wps2)
			return -1;
#else /* WPS_STRICT_WPS2 */
		return -1;
#endif /* WPS_STRICT_WPS2 */
	}

	return 0;
}