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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  tstats ;
struct ecore_ptt {int dummy; } ;
struct ecore_ll2_stats {int /*<<< orphan*/  no_buff_discard; int /*<<< orphan*/  packet_too_big_discard; } ;
struct ecore_ll2_info {int /*<<< orphan*/  queue_id; } ;
struct ecore_hwfn {int dummy; } ;
struct core_ll2_tstorm_per_queue_stat {int /*<<< orphan*/  no_buff_discard; int /*<<< orphan*/  packet_too_big_discard; } ;

/* Variables and functions */
 scalar_t__ BAR0_MAP_REG_TSDM_RAM ; 
 scalar_t__ CORE_LL2_TSTORM_PER_QUEUE_STAT_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ HILO_64_REGPAIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct core_ll2_tstorm_per_queue_stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_memcpy_from (struct ecore_hwfn*,struct ecore_ptt*,struct core_ll2_tstorm_per_queue_stat*,scalar_t__,int) ; 

__attribute__((used)) static void _ecore_ll2_get_tstats(struct ecore_hwfn *p_hwfn,
				  struct ecore_ptt *p_ptt,
				  struct ecore_ll2_info *p_ll2_conn,
				  struct ecore_ll2_stats *p_stats)
{
	struct core_ll2_tstorm_per_queue_stat tstats;
	u8 qid = p_ll2_conn->queue_id;
	u32 tstats_addr;

	OSAL_MEMSET(&tstats, 0, sizeof(tstats));
	tstats_addr = BAR0_MAP_REG_TSDM_RAM +
		      CORE_LL2_TSTORM_PER_QUEUE_STAT_OFFSET(qid);
	ecore_memcpy_from(p_hwfn, p_ptt, &tstats,
			  tstats_addr,
			  sizeof(tstats));

	p_stats->packet_too_big_discard +=
		HILO_64_REGPAIR(tstats.packet_too_big_discard);
	p_stats->no_buff_discard +=
		HILO_64_REGPAIR(tstats.no_buff_discard);
}