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
 scalar_t__ OCV_OCI_LEN ; 
 int /*<<< orphan*/  WLAN_EID_EXTENSION ; 
 scalar_t__ WLAN_EID_EXT_OCV_OCI ; 
 int ocv_insert_oci (struct wpa_channel_info*,int /*<<< orphan*/ **) ; 

int ocv_insert_extended_oci(struct wpa_channel_info *ci, u8 *pos)
{
	*pos++ = WLAN_EID_EXTENSION;
	*pos++ = 1 + OCV_OCI_LEN;
	*pos++ = WLAN_EID_EXT_OCV_OCI;
	return ocv_insert_oci(ci, &pos);
}