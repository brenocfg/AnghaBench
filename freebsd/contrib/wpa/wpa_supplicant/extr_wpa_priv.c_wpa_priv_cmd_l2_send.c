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
typedef  int /*<<< orphan*/  u16 ;
struct wpa_priv_interface {int /*<<< orphan*/ ** l2; int /*<<< orphan*/ * l2_addr; int /*<<< orphan*/ * l2_addr_len; } ;
struct sockaddr_un {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_PRIV_MAX_L2 ; 
 int l2_packet_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ *,struct sockaddr_un*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_priv_allowed_l2_proto (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpa_priv_cmd_l2_send(struct wpa_priv_interface *iface,
				 struct sockaddr_un *from, socklen_t fromlen,
				 void *buf, size_t len)
{
	u8 *dst_addr;
	u16 proto;
	int res;
	int idx;

	for (idx = 0; idx < WPA_PRIV_MAX_L2; idx++) {
		if (iface->l2_addr_len[idx] == fromlen &&
		    os_memcmp(&iface->l2_addr[idx], from, fromlen) == 0)
			break;
	}
	if (idx == WPA_PRIV_MAX_L2) {
		wpa_printf(MSG_DEBUG,
			   "No registered l2_packet socket found for send request");
		return;
	}

	if (iface->l2[idx] == NULL)
		return;

	if (len < ETH_ALEN + 2) {
		wpa_printf(MSG_DEBUG, "Too short L2 send packet (len=%lu)",
			   (unsigned long) len);
		return;
	}

	dst_addr = buf;
	os_memcpy(&proto, buf + ETH_ALEN, 2);

	if (!wpa_priv_allowed_l2_proto(proto)) {
		wpa_printf(MSG_DEBUG, "Refused l2_packet send for ethertype "
			   "0x%x", proto);
		return;
	}

	res = l2_packet_send(iface->l2[idx], dst_addr, proto,
			     buf + ETH_ALEN + 2, len - ETH_ALEN - 2);
	wpa_printf(MSG_DEBUG, "L2 send[idx=%d]: res=%d", idx, res);
}