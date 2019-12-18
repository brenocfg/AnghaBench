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
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  P2P_IE_VENDOR_TYPE ; 
 int /*<<< orphan*/  WLAN_ACTION_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

void p2p_buf_add_action_hdr(struct wpabuf *buf, u8 subtype, u8 dialog_token)
{
	wpabuf_put_u8(buf, WLAN_ACTION_VENDOR_SPECIFIC);
	wpabuf_put_be32(buf, P2P_IE_VENDOR_TYPE);

	wpabuf_put_u8(buf, subtype); /* OUI Subtype */
	wpabuf_put_u8(buf, dialog_token);
	wpa_printf(MSG_DEBUG, "P2P: * Dialog Token: %d", dialog_token);
}