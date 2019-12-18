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
typedef  int /*<<< orphan*/  ustats ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct eth_ustorm_per_queue_stat {int /*<<< orphan*/  rcv_bcast_pkts; int /*<<< orphan*/  rcv_mcast_pkts; int /*<<< orphan*/  rcv_ucast_pkts; int /*<<< orphan*/  rcv_bcast_bytes; int /*<<< orphan*/  rcv_mcast_bytes; int /*<<< orphan*/  rcv_ucast_bytes; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bcast_pkts; int /*<<< orphan*/  rx_mcast_pkts; int /*<<< orphan*/  rx_ucast_pkts; int /*<<< orphan*/  rx_bcast_bytes; int /*<<< orphan*/  rx_mcast_bytes; int /*<<< orphan*/  rx_ucast_bytes; } ;
struct ecore_eth_stats {TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ HILO_64_REGPAIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct eth_ustorm_per_queue_stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __ecore_get_vport_ustats_addrlen (struct ecore_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_memcpy_from (struct ecore_hwfn*,struct ecore_ptt*,struct eth_ustorm_per_queue_stat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ecore_get_vport_ustats(struct ecore_hwfn *p_hwfn,
				     struct ecore_ptt *p_ptt,
				     struct ecore_eth_stats *p_stats,
				     u16 statistics_bin)
{
	struct eth_ustorm_per_queue_stat ustats;
	u32 ustats_addr = 0, ustats_len = 0;

	__ecore_get_vport_ustats_addrlen(p_hwfn, &ustats_addr, &ustats_len,
					 statistics_bin);

	OSAL_MEMSET(&ustats, 0, sizeof(ustats));
	ecore_memcpy_from(p_hwfn, p_ptt, &ustats,
			  ustats_addr, ustats_len);

	p_stats->common.rx_ucast_bytes +=
		HILO_64_REGPAIR(ustats.rcv_ucast_bytes);
	p_stats->common.rx_mcast_bytes +=
		HILO_64_REGPAIR(ustats.rcv_mcast_bytes);
	p_stats->common.rx_bcast_bytes +=
		HILO_64_REGPAIR(ustats.rcv_bcast_bytes);
	p_stats->common.rx_ucast_pkts +=
		HILO_64_REGPAIR(ustats.rcv_ucast_pkts);
	p_stats->common.rx_mcast_pkts +=
		HILO_64_REGPAIR(ustats.rcv_mcast_pkts);
	p_stats->common.rx_bcast_pkts +=
		HILO_64_REGPAIR(ustats.rcv_bcast_pkts);
}