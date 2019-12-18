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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct wpa_scan_res {int ie_len; } ;

/* Variables and functions */
 int const WLAN_EID_VENDOR_SPECIFIC ; 
 scalar_t__ WPA_GET_BE32 (int const*) ; 

const u8 * wpa_scan_get_vendor_ie(const struct wpa_scan_res *res,
				  u32 vendor_type)
{
	const u8 *end, *pos;

	pos = (const u8 *) (res + 1);
	end = pos + res->ie_len;

	while (end - pos > 1) {
		if (2 + pos[1] > end - pos)
			break;
		if (pos[0] == WLAN_EID_VENDOR_SPECIFIC && pos[1] >= 4 &&
		    vendor_type == WPA_GET_BE32(&pos[2]))
			return pos;
		pos += 2 + pos[1];
	}

	return NULL;
}