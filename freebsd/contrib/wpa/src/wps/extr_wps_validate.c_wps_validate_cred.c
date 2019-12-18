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
typedef  int /*<<< orphan*/  u8 ;
struct wps_parse_attr {int /*<<< orphan*/  network_key_shareable; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  encr_type; int /*<<< orphan*/  network_key_len; int /*<<< orphan*/  network_key; int /*<<< orphan*/  network_key_idx; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  network_idx; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_set (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ wps_parse_msg (struct wpabuf*,struct wps_parse_attr*) ; 
 scalar_t__ wps_validate_auth_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_encr_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_mac_addr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_network_idx (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_network_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_network_key_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_validate_network_key_shareable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_validate_ssid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wps_validate_cred(const u8 *cred, size_t len)
{
	struct wps_parse_attr attr;
	struct wpabuf buf;

	if (cred == NULL)
		return -1;
	wpabuf_set(&buf, cred, len);
	if (wps_parse_msg(&buf, &attr) < 0) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Failed to parse Credential");
		return -1;
	}

	if (wps_validate_network_idx(attr.network_idx, 1) ||
	    wps_validate_ssid(attr.ssid, attr.ssid_len, 1) ||
	    wps_validate_auth_type(attr.auth_type, 1) ||
	    wps_validate_encr_type(attr.encr_type, 1) ||
	    wps_validate_network_key_index(attr.network_key_idx, 0) ||
	    wps_validate_network_key(attr.network_key, attr.network_key_len,
				     attr.encr_type, 1) ||
	    wps_validate_mac_addr(attr.mac_addr, 1) ||
	    wps_validate_network_key_shareable(attr.network_key_shareable, 0))
	{
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid Credential");
		return -1;
	}


	return 0;
}