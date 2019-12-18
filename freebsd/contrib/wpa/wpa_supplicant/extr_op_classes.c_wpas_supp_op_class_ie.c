#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct wpabuf {int dummy; } ;
struct wpa_supplicant {int dummy; } ;
struct wpa_ssid {int dummy; } ;
struct TYPE_3__ {size_t op_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANWIDTH_USE_HT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ NUM_HOSTAPD_MODES ; 
 size_t WLAN_EID_SUPPORTED_OPERATING_CLASSES ; 
 TYPE_1__* global_op_class ; 
 scalar_t__ global_op_class_size ; 
 scalar_t__ ieee80211_freq_to_channel_ext (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t*) ; 
 int /*<<< orphan*/  os_memcpy (size_t*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 
 size_t* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,size_t) ; 
 scalar_t__ wpas_op_class_supported (struct wpa_supplicant*,struct wpa_ssid*,TYPE_1__*) ; 

size_t wpas_supp_op_class_ie(struct wpa_supplicant *wpa_s,
			     struct wpa_ssid *ssid,
			     int freq, u8 *pos, size_t len)
{
	struct wpabuf *buf;
	u8 op, current, chan;
	u8 *ie_len;
	size_t res;

	/*
	 * Assume 20 MHz channel for now.
	 * TODO: Use the secondary channel and VHT channel width that will be
	 * used after association.
	 */
	if (ieee80211_freq_to_channel_ext(freq, 0, CHANWIDTH_USE_HT,
					  &current, &chan) == NUM_HOSTAPD_MODES)
		return 0;

	/*
	 * Need 3 bytes for EID, length, and current operating class, plus
	 * 1 byte for every other supported operating class.
	 */
	buf = wpabuf_alloc(global_op_class_size + 3);
	if (!buf)
		return 0;

	wpabuf_put_u8(buf, WLAN_EID_SUPPORTED_OPERATING_CLASSES);
	/* Will set the length later, putting a placeholder */
	ie_len = wpabuf_put(buf, 1);
	wpabuf_put_u8(buf, current);

	for (op = 0; global_op_class[op].op_class; op++) {
		if (wpas_op_class_supported(wpa_s, ssid, &global_op_class[op]))
			wpabuf_put_u8(buf, global_op_class[op].op_class);
	}

	*ie_len = wpabuf_len(buf) - 2;
	if (*ie_len < 2 || wpabuf_len(buf) > len) {
		wpa_printf(MSG_ERROR,
			   "Failed to add supported operating classes IE");
		res = 0;
	} else {
		os_memcpy(pos, wpabuf_head(buf), wpabuf_len(buf));
		res = wpabuf_len(buf);
		wpa_hexdump_buf(MSG_DEBUG,
				"Added supported operating classes IE", buf);
	}

	wpabuf_free(buf);
	return res;
}