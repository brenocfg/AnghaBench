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
struct TYPE_2__ {int /*<<< orphan*/  syn_phy_addr_hi; int /*<<< orphan*/  syn_phy_addr_lo; int /*<<< orphan*/  syn_ip_payload_length; int /*<<< orphan*/  connect_mode; int /*<<< orphan*/  rcv_wnd_scale; int /*<<< orphan*/  mss; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  local_port; int /*<<< orphan*/  tos_or_tc; int /*<<< orphan*/  ttl; int /*<<< orphan*/  flow_label; int /*<<< orphan*/ * remote_ip; int /*<<< orphan*/ * local_ip; int /*<<< orphan*/  ip_version; int /*<<< orphan*/  flags; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  remote_mac_addr_hi; int /*<<< orphan*/  remote_mac_addr_mid; int /*<<< orphan*/  remote_mac_addr_lo; int /*<<< orphan*/  local_mac_addr_hi; int /*<<< orphan*/  local_mac_addr_mid; int /*<<< orphan*/  local_mac_addr_lo; } ;
struct iwarp_tcp_offload_ramrod_data {TYPE_1__ tcp; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 

__attribute__((used)) static void
ecore_iwarp_print_tcp_ramrod(struct ecore_hwfn *p_hwfn,
			     struct iwarp_tcp_offload_ramrod_data *p_tcp_ramrod)
{
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, ">>> PRINT TCP RAMROD\n");

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "local_mac=%x %x %x\n",
		   p_tcp_ramrod->tcp.local_mac_addr_lo,
		   p_tcp_ramrod->tcp.local_mac_addr_mid,
		   p_tcp_ramrod->tcp.local_mac_addr_hi);

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "remote_mac=%x %x %x\n",
		   p_tcp_ramrod->tcp.remote_mac_addr_lo,
		   p_tcp_ramrod->tcp.remote_mac_addr_mid,
		   p_tcp_ramrod->tcp.remote_mac_addr_hi);

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "vlan_id=%x\n",
		   p_tcp_ramrod->tcp.vlan_id);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "flags=%x\n",
		   p_tcp_ramrod->tcp.flags);

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "ip_version=%x\n",
		   p_tcp_ramrod->tcp.ip_version);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "local_ip=%x.%x.%x.%x\n",
		   p_tcp_ramrod->tcp.local_ip[0],
		   p_tcp_ramrod->tcp.local_ip[1],
		   p_tcp_ramrod->tcp.local_ip[2],
		   p_tcp_ramrod->tcp.local_ip[3]);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "remote_ip=%x.%x.%x.%x\n",
		   p_tcp_ramrod->tcp.remote_ip[0],
		   p_tcp_ramrod->tcp.remote_ip[1],
		   p_tcp_ramrod->tcp.remote_ip[2],
		   p_tcp_ramrod->tcp.remote_ip[3]);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "flow_label=%x\n",
		   p_tcp_ramrod->tcp.flow_label);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "ttl=%x\n",
		   p_tcp_ramrod->tcp.ttl);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "tos_or_tc=%x\n",
		   p_tcp_ramrod->tcp.tos_or_tc);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "local_port=%x\n",
		   p_tcp_ramrod->tcp.local_port);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "remote_port=%x\n",
		   p_tcp_ramrod->tcp.remote_port);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "mss=%x\n",
		   p_tcp_ramrod->tcp.mss);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "rcv_wnd_scale=%x\n",
		   p_tcp_ramrod->tcp.rcv_wnd_scale);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "connect_mode=%x\n",
		   p_tcp_ramrod->tcp.connect_mode);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "syn_ip_payload_length=%x\n",
		   p_tcp_ramrod->tcp.syn_ip_payload_length);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "syn_phy_addr_lo=%x\n",
		   p_tcp_ramrod->tcp.syn_phy_addr_lo);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "syn_phy_addr_hi=%x\n",
		   p_tcp_ramrod->tcp.syn_phy_addr_hi);

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "<<<f  PRINT TCP RAMROD\n");
}