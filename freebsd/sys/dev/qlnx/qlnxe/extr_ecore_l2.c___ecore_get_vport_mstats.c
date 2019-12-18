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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct eth_mstorm_per_queue_stat {int /*<<< orphan*/  tpa_coalesced_bytes; int /*<<< orphan*/  tpa_aborts_num; int /*<<< orphan*/  tpa_coalesced_events; int /*<<< orphan*/  tpa_coalesced_pkts; int /*<<< orphan*/  ttl0_discard; int /*<<< orphan*/  packet_too_big_discard; int /*<<< orphan*/  no_buff_discard; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tpa_coalesced_bytes; int /*<<< orphan*/  tpa_aborts_num; int /*<<< orphan*/  tpa_coalesced_events; int /*<<< orphan*/  tpa_coalesced_pkts; int /*<<< orphan*/  ttl0_discard; int /*<<< orphan*/  packet_too_big_discard; int /*<<< orphan*/  no_buff_discards; } ;
struct ecore_eth_stats {TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  mstats ;

/* Variables and functions */
 scalar_t__ HILO_64_REGPAIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct eth_mstorm_per_queue_stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __ecore_get_vport_mstats_addrlen (struct ecore_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_memcpy_from (struct ecore_hwfn*,struct ecore_ptt*,struct eth_mstorm_per_queue_stat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ecore_get_vport_mstats(struct ecore_hwfn *p_hwfn,
				     struct ecore_ptt *p_ptt,
				     struct ecore_eth_stats *p_stats,
				     u16 statistics_bin)
{
	struct eth_mstorm_per_queue_stat mstats;
	u32 mstats_addr = 0, mstats_len = 0;

	__ecore_get_vport_mstats_addrlen(p_hwfn, &mstats_addr, &mstats_len,
					 statistics_bin);

	OSAL_MEMSET(&mstats, 0, sizeof(mstats));
	ecore_memcpy_from(p_hwfn, p_ptt, &mstats,
			  mstats_addr, mstats_len);

	p_stats->common.no_buff_discards +=
		HILO_64_REGPAIR(mstats.no_buff_discard);
	p_stats->common.packet_too_big_discard +=
		HILO_64_REGPAIR(mstats.packet_too_big_discard);
	p_stats->common.ttl0_discard +=
		HILO_64_REGPAIR(mstats.ttl0_discard);
	p_stats->common.tpa_coalesced_pkts +=
		HILO_64_REGPAIR(mstats.tpa_coalesced_pkts);
	p_stats->common.tpa_coalesced_events +=
		HILO_64_REGPAIR(mstats.tpa_coalesced_events);
	p_stats->common.tpa_aborts_num +=
		HILO_64_REGPAIR(mstats.tpa_aborts_num);
	p_stats->common.tpa_coalesced_bytes +=
		HILO_64_REGPAIR(mstats.tpa_coalesced_bytes);
}