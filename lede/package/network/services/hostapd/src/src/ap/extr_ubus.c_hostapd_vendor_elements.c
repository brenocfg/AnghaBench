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
struct wpabuf {int dummy; } ;
struct ubus_request_data {int dummy; } ;
struct ubus_object {int dummy; } ;
struct ubus_context {int dummy; } ;
struct hostapd_data {int /*<<< orphan*/  iface; struct hostapd_bss_config* conf; } ;
struct hostapd_bss_config {struct wpabuf* vendor_elements; } ;
struct blob_attr {int dummy; } ;

/* Variables and functions */
 int UBUS_STATUS_INVALID_ARGUMENT ; 
 int UBUS_STATUS_NOT_SUPPORTED ; 
 int UBUS_STATUS_OK ; 
 size_t VENDOR_ELEMENTS ; 
 int __VENDOR_ELEMENTS_MAX ; 
 int /*<<< orphan*/  blob_data (struct blob_attr*) ; 
 int /*<<< orphan*/  blob_len (struct blob_attr*) ; 
 char* blobmsg_data (struct blob_attr*) ; 
 int /*<<< orphan*/  blobmsg_parse (int /*<<< orphan*/ ,int,struct blob_attr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hostapd_data* get_hapd_from_object (struct ubus_object*) ; 
 scalar_t__ hexstr2bin (char const*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ieee802_11_update_beacons (int /*<<< orphan*/ ) ; 
 size_t os_strlen (char const*) ; 
 int /*<<< orphan*/  ve_policy ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,size_t) ; 

__attribute__((used)) static int
hostapd_vendor_elements(struct ubus_context *ctx, struct ubus_object *obj,
			struct ubus_request_data *req, const char *method,
			struct blob_attr *msg)
{
	struct blob_attr *tb[__VENDOR_ELEMENTS_MAX];
	struct hostapd_data *hapd = get_hapd_from_object(obj);
	struct hostapd_bss_config *bss = hapd->conf;
	struct wpabuf *elems;
	const char *pos;
	size_t len;

	blobmsg_parse(ve_policy, __VENDOR_ELEMENTS_MAX, tb,
		      blob_data(msg), blob_len(msg));

	if (!tb[VENDOR_ELEMENTS])
		return UBUS_STATUS_INVALID_ARGUMENT;

	pos = blobmsg_data(tb[VENDOR_ELEMENTS]);
	len = os_strlen(pos);
	if (len & 0x01)
			return UBUS_STATUS_INVALID_ARGUMENT;

	len /= 2;
	if (len == 0) {
		wpabuf_free(bss->vendor_elements);
		bss->vendor_elements = NULL;
		return 0;
	}

	elems = wpabuf_alloc(len);
	if (elems == NULL)
		return 1;

	if (hexstr2bin(pos, wpabuf_put(elems, len), len)) {
		wpabuf_free(elems);
		return UBUS_STATUS_INVALID_ARGUMENT;
	}

	wpabuf_free(bss->vendor_elements);
	bss->vendor_elements = elems;

	/* update beacons if vendor elements were set successfully */
	if (ieee802_11_update_beacons(hapd->iface) != 0)
		return UBUS_STATUS_NOT_SUPPORTED;
	return UBUS_STATUS_OK;
}