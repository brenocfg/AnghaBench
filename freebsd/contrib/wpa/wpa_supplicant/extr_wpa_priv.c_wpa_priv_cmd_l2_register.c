#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wpa_priv_interface {int /*<<< orphan*/  fd; int /*<<< orphan*/ ** l2; TYPE_1__* l2_ctx; int /*<<< orphan*/  ifname; int /*<<< orphan*/ * l2_addr_len; int /*<<< orphan*/ * l2_addr; } ;
struct sockaddr_un {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_2__ {int idx; struct wpa_priv_interface* parent; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_PRIV_MAX_L2 ; 
 int /*<<< orphan*/  l2_packet_deinit (int /*<<< orphan*/ *) ; 
 scalar_t__ l2_packet_get_own_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * l2_packet_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,struct sockaddr_un*,int /*<<< orphan*/ ) ; 
 int sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_priv_allowed_l2_proto (int) ; 
 int /*<<< orphan*/  wpa_priv_l2_rx ; 

__attribute__((used)) static void wpa_priv_cmd_l2_register(struct wpa_priv_interface *iface,
				     struct sockaddr_un *from,
				     socklen_t fromlen,
				     void *buf, size_t len)
{
	int *reg_cmd = buf;
	u8 own_addr[ETH_ALEN];
	int res;
	u16 proto;
	int idx;

	if (len != 2 * sizeof(int)) {
		wpa_printf(MSG_DEBUG, "Invalid l2_register length %lu",
			   (unsigned long) len);
		return;
	}

	proto = reg_cmd[0];
	if (!wpa_priv_allowed_l2_proto(proto)) {
		wpa_printf(MSG_DEBUG, "Refused l2_packet connection for "
			   "ethertype 0x%x", proto);
		return;
	}

	for (idx = 0; idx < WPA_PRIV_MAX_L2; idx++) {
		if (!iface->l2[idx])
			break;
	}
	if (idx == WPA_PRIV_MAX_L2) {
		wpa_printf(MSG_DEBUG, "No free l2_packet connection found");
		return;
	}

	os_memcpy(&iface->l2_addr[idx], from, fromlen);
	iface->l2_addr_len[idx] = fromlen;

	iface->l2_ctx[idx].idx = idx;
	iface->l2_ctx[idx].parent = iface;
	iface->l2[idx] = l2_packet_init(iface->ifname, NULL, proto,
					wpa_priv_l2_rx, &iface->l2_ctx[idx],
					reg_cmd[1]);
	if (!iface->l2[idx]) {
		wpa_printf(MSG_DEBUG, "Failed to initialize l2_packet "
			   "instance for protocol %d", proto);
		return;
	}

	if (l2_packet_get_own_addr(iface->l2[idx], own_addr) < 0) {
		wpa_printf(MSG_DEBUG, "Failed to get own address from "
			   "l2_packet");
		l2_packet_deinit(iface->l2[idx]);
		iface->l2[idx] = NULL;
		return;
	}

	res = sendto(iface->fd, own_addr, ETH_ALEN, 0,
		     (struct sockaddr *) from, fromlen);
	wpa_printf(MSG_DEBUG, "L2 registration[idx=%d]: res=%d", idx, res);
}