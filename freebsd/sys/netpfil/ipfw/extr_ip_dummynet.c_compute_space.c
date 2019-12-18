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
typedef  int /*<<< orphan*/  uint32_t ;
struct dn_sch {int dummy; } ;
struct dn_profile {int dummy; } ;
struct dn_link {int dummy; } ;
struct dn_id {int subtype; } ;
struct dn_fs {int dummy; } ;
struct dn_flow {int dummy; } ;
struct copy_args {int flags; } ;
struct TYPE_2__ {int schk_count; int fsk_count; int queue_count; int si_count; } ;

/* Variables and functions */
 int DN_C_FLOW ; 
 int DN_C_FS ; 
 int DN_C_LINK ; 
 int DN_C_QUEUE ; 
 int DN_C_SCH ; 
#define  DN_FS 131 
#define  DN_GET_COMPAT 130 
#define  DN_LINK 129 
#define  DN_SCH 128 
 int ED_MAX_SAMPLES_NO ; 
 TYPE_1__ dn_cfg ; 
 int dn_compat_calc_size () ; 

__attribute__((used)) static int
compute_space(struct dn_id *cmd, struct copy_args *a)
{
	int x = 0, need = 0;
	int profile_size = sizeof(struct dn_profile) - 
		ED_MAX_SAMPLES_NO*sizeof(int);

	/* NOTE about compute space:
	 * NP 	= dn_cfg.schk_count
	 * NSI 	= dn_cfg.si_count
	 * NF 	= dn_cfg.fsk_count
	 * NQ 	= dn_cfg.queue_count
	 * - ipfw pipe show
	 *   (NP/2)*(dn_link + dn_sch + dn_id + dn_fs) only half scheduler
	 *                             link, scheduler template, flowset
	 *                             integrated in scheduler and header
	 *                             for flowset list
	 *   (NSI)*(dn_flow) all scheduler instance (includes
	 *                              the queue instance)
	 * - ipfw sched show
	 *   (NP/2)*(dn_link + dn_sch + dn_id + dn_fs) only half scheduler
	 *                             link, scheduler template, flowset
	 *                             integrated in scheduler and header
	 *                             for flowset list
	 *   (NSI * dn_flow) all scheduler instances
	 *   (NF * sizeof(uint_32)) space for flowset list linked to scheduler
	 *   (NQ * dn_queue) all queue [XXXfor now not listed]
	 * - ipfw queue show
	 *   (NF * dn_fs) all flowset
	 *   (NQ * dn_queue) all queues
	 */
	switch (cmd->subtype) {
	default:
		return -1;
	/* XXX where do LINK and SCH differ ? */
	/* 'ipfw sched show' could list all queues associated to
	 * a scheduler. This feature for now is disabled
	 */
	case DN_LINK:	/* pipe show */
		x = DN_C_LINK | DN_C_SCH | DN_C_FLOW;
		need += dn_cfg.schk_count *
			(sizeof(struct dn_fs) + profile_size) / 2;
		need += dn_cfg.fsk_count * sizeof(uint32_t);
		break;
	case DN_SCH:	/* sched show */
		need += dn_cfg.schk_count *
			(sizeof(struct dn_fs) + profile_size) / 2;
		need += dn_cfg.fsk_count * sizeof(uint32_t);
		x = DN_C_SCH | DN_C_LINK | DN_C_FLOW;
		break;
	case DN_FS:	/* queue show */
		x = DN_C_FS | DN_C_QUEUE;
		break;
	case DN_GET_COMPAT:	/* compatibility mode */
		need =  dn_compat_calc_size(); 
		break;
	}
	a->flags = x;
	if (x & DN_C_SCH) {
		need += dn_cfg.schk_count * sizeof(struct dn_sch) / 2;
		/* NOT also, each fs might be attached to a sched */
		need += dn_cfg.schk_count * sizeof(struct dn_id) / 2;
	}
	if (x & DN_C_FS)
		need += dn_cfg.fsk_count * sizeof(struct dn_fs);
	if (x & DN_C_LINK) {
		need += dn_cfg.schk_count * sizeof(struct dn_link) / 2;
	}
	/*
	 * When exporting a queue to userland, only pass up the
	 * struct dn_flow, which is the only visible part.
	 */

	if (x & DN_C_QUEUE)
		need += dn_cfg.queue_count * sizeof(struct dn_flow);
	if (x & DN_C_FLOW)
		need += dn_cfg.si_count * (sizeof(struct dn_flow));
	return need;
}