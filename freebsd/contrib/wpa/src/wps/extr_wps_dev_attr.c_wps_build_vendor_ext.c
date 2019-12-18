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
struct wps_device_data {int /*<<< orphan*/ ** vendor_ext; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_VENDOR_EXT ; 
 int MAX_WPS_VENDOR_EXTENSIONS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_head_u8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,int /*<<< orphan*/ *) ; 

int wps_build_vendor_ext(struct wps_device_data *dev, struct wpabuf *msg)
{
	int i;

	for (i = 0; i < MAX_WPS_VENDOR_EXTENSIONS; i++) {
		if (dev->vendor_ext[i] == NULL)
			continue;
		wpa_hexdump(MSG_DEBUG, "WPS:  * Vendor Extension",
			    wpabuf_head_u8(dev->vendor_ext[i]),
			    wpabuf_len(dev->vendor_ext[i]));
		wpabuf_put_be16(msg, ATTR_VENDOR_EXT);
		wpabuf_put_be16(msg, wpabuf_len(dev->vendor_ext[i]));
		wpabuf_put_buf(msg, dev->vendor_ext[i]);
	}

	return 0;
}