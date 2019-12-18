#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ib_pma_portcounters_ext {void* port_multicast_rcv_packets; void* port_multicast_xmit_packets; void* port_unicast_rcv_packets; void* port_unicast_xmit_packets; void* port_rcv_packets; void* port_xmit_packets; void* port_rcv_data; void* port_xmit_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  octets; } ;
struct TYPE_7__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  octets; } ;
struct TYPE_6__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  octets; } ;
struct TYPE_5__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  octets; } ;

/* Variables and functions */
 void* MLX5_GET64_BE (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_SUM_CNT (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int) ; 
 int /*<<< orphan*/  query_vport_counter_out ; 
 TYPE_4__ received_ib_multicast ; 
 TYPE_3__ received_ib_unicast ; 
 TYPE_2__ transmitted_ib_multicast ; 
 TYPE_1__ transmitted_ib_unicast ; 

__attribute__((used)) static void pma_cnt_ext_assign(struct ib_pma_portcounters_ext *pma_cnt_ext,
			       void *out)
{
#define MLX5_SUM_CNT(p, cntr1, cntr2)	\
	(MLX5_GET64(query_vport_counter_out, p, cntr1) + \
	MLX5_GET64(query_vport_counter_out, p, cntr2))

	pma_cnt_ext->port_xmit_data =
		cpu_to_be64(MLX5_SUM_CNT(out, transmitted_ib_unicast.octets,
					 transmitted_ib_multicast.octets) >> 2);
	pma_cnt_ext->port_rcv_data =
		cpu_to_be64(MLX5_SUM_CNT(out, received_ib_unicast.octets,
					 received_ib_multicast.octets) >> 2);
	pma_cnt_ext->port_xmit_packets =
		cpu_to_be64(MLX5_SUM_CNT(out, transmitted_ib_unicast.packets,
					 transmitted_ib_multicast.packets));
	pma_cnt_ext->port_rcv_packets =
		cpu_to_be64(MLX5_SUM_CNT(out, received_ib_unicast.packets,
					 received_ib_multicast.packets));
	pma_cnt_ext->port_unicast_xmit_packets =
		MLX5_GET64_BE(query_vport_counter_out,
			      out, transmitted_ib_unicast.packets);
	pma_cnt_ext->port_unicast_rcv_packets =
		MLX5_GET64_BE(query_vport_counter_out,
			      out, received_ib_unicast.packets);
	pma_cnt_ext->port_multicast_xmit_packets =
		MLX5_GET64_BE(query_vport_counter_out,
			      out, transmitted_ib_multicast.packets);
	pma_cnt_ext->port_multicast_rcv_packets =
		MLX5_GET64_BE(query_vport_counter_out,
			      out, received_ib_multicast.packets);
}