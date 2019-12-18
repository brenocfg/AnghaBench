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

/* Variables and functions */
 int /*<<< orphan*/  MBO_ATTR_ID_NON_PREF_CHAN_REPORT ; 
 int /*<<< orphan*/  OUI_WFA ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  wpabuf_put_be24 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_mbo_non_pref_chan_subelem_hdr(struct wpabuf *mbo, u8 len)
{
	wpabuf_put_u8(mbo, WLAN_EID_VENDOR_SPECIFIC);
	wpabuf_put_u8(mbo, len); /* Length */
	wpabuf_put_be24(mbo, OUI_WFA);
	wpabuf_put_u8(mbo, MBO_ATTR_ID_NON_PREF_CHAN_REPORT);
}