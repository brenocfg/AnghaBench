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
typedef  enum p2p_role_indication { ____Placeholder_p2p_role_indication } p2p_role_indication ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  P2P_ATTR_OOB_GO_NEG_CHANNEL ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char const*,int) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

void p2p_buf_add_oob_go_neg_channel(struct wpabuf *buf, const char *country,
				    u8 oper_class, u8 channel,
				    enum p2p_role_indication role)
{
	/* OOB Group Owner Negotiation Channel */
	wpabuf_put_u8(buf, P2P_ATTR_OOB_GO_NEG_CHANNEL);
	wpabuf_put_le16(buf, 6);
	wpabuf_put_data(buf, country, 3);
	wpabuf_put_u8(buf, oper_class); /* Operating Class */
	wpabuf_put_u8(buf, channel); /* Channel Number */
	wpabuf_put_u8(buf, (u8) role); /* Role indication */
	wpa_printf(MSG_DEBUG, "P2P: * OOB GO Negotiation Channel: Operating "
		   "Class %u Channel %u Role %d",
		   oper_class, channel, role);
}