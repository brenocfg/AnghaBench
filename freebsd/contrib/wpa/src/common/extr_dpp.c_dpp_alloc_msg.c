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
typedef  enum dpp_public_action_frame_type { ____Placeholder_dpp_public_action_frame_type } dpp_public_action_frame_type ;

/* Variables and functions */
 int DPP_OUI_TYPE ; 
 int /*<<< orphan*/  OUI_WFA ; 
 int WLAN_ACTION_PUBLIC ; 
 int WLAN_PA_VENDOR_SPECIFIC ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_be24 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

struct wpabuf * dpp_alloc_msg(enum dpp_public_action_frame_type type,
			      size_t len)
{
	struct wpabuf *msg;

	msg = wpabuf_alloc(8 + len);
	if (!msg)
		return NULL;
	wpabuf_put_u8(msg, WLAN_ACTION_PUBLIC);
	wpabuf_put_u8(msg, WLAN_PA_VENDOR_SPECIFIC);
	wpabuf_put_be24(msg, OUI_WFA);
	wpabuf_put_u8(msg, DPP_OUI_TYPE);
	wpabuf_put_u8(msg, 1); /* Crypto Suite */
	wpabuf_put_u8(msg, type);
	return msg;
}