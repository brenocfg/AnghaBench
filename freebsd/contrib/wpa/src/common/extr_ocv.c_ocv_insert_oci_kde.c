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
struct wpa_channel_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSN_KEY_DATA_OCI ; 
 scalar_t__ RSN_SELECTOR_LEN ; 
 int /*<<< orphan*/  RSN_SELECTOR_PUT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int ocv_insert_oci (struct wpa_channel_info*,int /*<<< orphan*/ **) ; 

int ocv_insert_oci_kde(struct wpa_channel_info *ci, u8 **argpos)
{
	u8 *pos = *argpos;

	*pos++ = WLAN_EID_VENDOR_SPECIFIC;
	*pos++ = RSN_SELECTOR_LEN + 3;
	RSN_SELECTOR_PUT(pos, RSN_KEY_DATA_OCI);
	pos += RSN_SELECTOR_LEN;

	*argpos = pos;
	return ocv_insert_oci(ci, argpos);
}