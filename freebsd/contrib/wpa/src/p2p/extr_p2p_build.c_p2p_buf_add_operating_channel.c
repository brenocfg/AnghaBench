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
 int /*<<< orphan*/  P2P_ATTR_OPERATING_CHANNEL ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char const*,int) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

void p2p_buf_add_operating_channel(struct wpabuf *buf, const char *country,
				   u8 reg_class, u8 channel)
{
	/* Operating Channel */
	wpabuf_put_u8(buf, P2P_ATTR_OPERATING_CHANNEL);
	wpabuf_put_le16(buf, 5);
	wpabuf_put_data(buf, country, 3);
	wpabuf_put_u8(buf, reg_class); /* Regulatory Class */
	wpabuf_put_u8(buf, channel); /* Channel Number */
	wpa_printf(MSG_DEBUG, "P2P: * Operating Channel: Regulatory Class %u "
		   "Channel %u", reg_class, channel);
}