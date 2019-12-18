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
struct wpabuf {int dummy; } ;
struct wpa_config {struct wpabuf* ap_vendor_elements; } ;
struct global_parse_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ hexstr2bin (char const*,int /*<<< orphan*/ *,int) ; 
 int os_strlen (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static int wpa_config_process_ap_vendor_elements(
	const struct global_parse_data *data,
	struct wpa_config *config, int line, const char *pos)
{
	struct wpabuf *tmp;
	int len = os_strlen(pos) / 2;
	u8 *p;

	if (!len) {
		wpa_printf(MSG_ERROR, "Line %d: invalid ap_vendor_elements",
			   line);
		return -1;
	}

	tmp = wpabuf_alloc(len);
	if (tmp) {
		p = wpabuf_put(tmp, len);

		if (hexstr2bin(pos, p, len)) {
			wpa_printf(MSG_ERROR, "Line %d: invalid "
				   "ap_vendor_elements", line);
			wpabuf_free(tmp);
			return -1;
		}

		wpabuf_free(config->ap_vendor_elements);
		config->ap_vendor_elements = tmp;
	} else {
		wpa_printf(MSG_ERROR, "Cannot allocate memory for "
			   "ap_vendor_elements");
		return -1;
	}

	return 0;
}