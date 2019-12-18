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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int P2P_ATTR_GROUP_OWNER_INTENT ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

void p2p_buf_add_go_intent(struct wpabuf *buf, u8 go_intent)
{
	/* Group Owner Intent */
	wpabuf_put_u8(buf, P2P_ATTR_GROUP_OWNER_INTENT);
	wpabuf_put_le16(buf, 1);
	wpabuf_put_u8(buf, go_intent);
	wpa_printf(MSG_DEBUG, "P2P: * GO Intent: Intent %u Tie breaker %u",
		   go_intent >> 1, go_intent & 0x01);
}