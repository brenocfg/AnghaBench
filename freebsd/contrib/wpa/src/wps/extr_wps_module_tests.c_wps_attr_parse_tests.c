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
struct wps_parse_attr {int /*<<< orphan*/  settings_delay_time; int /*<<< orphan*/  request_to_enroll; int /*<<< orphan*/  network_key_shareable; int /*<<< orphan*/  authorized_macs; int /*<<< orphan*/  version2; int /*<<< orphan*/  num_vendor_ext; int /*<<< orphan*/  num_req_dev_type; int /*<<< orphan*/  network_key_idx; int /*<<< orphan*/  num_cred; int /*<<< orphan*/  ap_setup_locked; int /*<<< orphan*/  network_key; } ;
struct wps_attr_parse_test {scalar_t__ result; int extra; int /*<<< orphan*/  data; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct wps_attr_parse_test*) ; 
 int /*<<< orphan*/  MAX_CRED_COUNT ; 
 int /*<<< orphan*/  MAX_REQ_DEV_TYPE_COUNT ; 
 int /*<<< orphan*/  MAX_WPS_PARSE_VENDOR_EXT ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ hexstr2bin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int os_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,size_t) ; 
 struct wps_attr_parse_test* wps_attr_parse_test_cases ; 
 scalar_t__ wps_parse_msg (struct wpabuf*,struct wps_parse_attr*) ; 

__attribute__((used)) static int wps_attr_parse_tests(void)
{
	struct wps_parse_attr attr;
	unsigned int i;
	int ret = 0;

	wpa_printf(MSG_INFO, "WPS attribute parsing tests");

	for (i = 0; i < ARRAY_SIZE(wps_attr_parse_test_cases); i++) {
		struct wpabuf *buf;
		size_t len;
		const struct wps_attr_parse_test *test =
			&wps_attr_parse_test_cases[i];

		len = os_strlen(test->data) / 2;
		buf = wpabuf_alloc(len);
		if (buf == NULL)
			return -1;
		if (hexstr2bin(test->data, wpabuf_put(buf, len), len) < 0) {
			wpabuf_free(buf);
			return -1;
		}
		if (wps_parse_msg(buf, &attr) != test->result) {
			wpa_printf(MSG_ERROR, "WPS attribute parsing test %u failed: %s",
				   i, test->data);
			ret = -1;
		}
		switch (test->extra) {
		case 1:
			if (!attr.network_key || !attr.ap_setup_locked)
				ret = -1;
			break;
		case 2:
			if (attr.num_cred != MAX_CRED_COUNT)
				ret = -1;
			break;
		case 3:
			if (!attr.network_key_idx)
				ret = -1;
			break;
		case 4:
			if (attr.num_req_dev_type != MAX_REQ_DEV_TYPE_COUNT)
				ret = -1;
			break;
		case 5:
			if (attr.num_vendor_ext != MAX_WPS_PARSE_VENDOR_EXT)
				ret = -1;
			break;
		case 6:
			if (!attr.version2 ||
			    !attr.authorized_macs ||
			    !attr.network_key_shareable ||
			    !attr.request_to_enroll ||
			    !attr.settings_delay_time)
				ret = -1;
			break;
		}
		wpabuf_free(buf);
	}

	return ret;
}