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

/* Variables and functions */
 int /*<<< orphan*/  MULTI_AP_OUI_TYPE ; 
 int /*<<< orphan*/  MULTI_AP_SUB_ELEM_TYPE ; 
 int /*<<< orphan*/  OUI_WFA ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  WPA_PUT_BE24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t add_multi_ap_ie(u8 *buf, size_t len, u8 value)
{
	u8 *pos = buf;

	if (len < 9)
		return 0;

	*pos++ = WLAN_EID_VENDOR_SPECIFIC;
	*pos++ = 7; /* len */
	WPA_PUT_BE24(pos, OUI_WFA);
	pos += 3;
	*pos++ = MULTI_AP_OUI_TYPE;
	*pos++ = MULTI_AP_SUB_ELEM_TYPE;
	*pos++ = 1; /* len */
	*pos++ = value;

	return pos - buf;
}