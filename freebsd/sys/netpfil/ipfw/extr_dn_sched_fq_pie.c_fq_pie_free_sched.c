#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fq_pie_si {TYPE_2__* si_extra; } ;
struct TYPE_3__ {int flows_cnt; } ;
struct fq_pie_schk {TYPE_1__ cfg; } ;
struct fq_pie_flow {int dummy; } ;
struct dn_sch_inst {scalar_t__ sched; } ;
struct TYPE_4__ {struct fq_pie_flow* flows; } ;

/* Variables and functions */
 int /*<<< orphan*/  pie_cleanup (struct fq_pie_flow*) ; 

__attribute__((used)) static int
fq_pie_free_sched(struct dn_sch_inst *_si)
{
	struct fq_pie_si *si;
	struct fq_pie_schk *schk;
	struct fq_pie_flow *flows;
	int i;

	si = (struct fq_pie_si *)_si;
	schk = (struct fq_pie_schk *)(_si->sched+1);
	flows = si->si_extra->flows;
	for (i = 0; i < schk->cfg.flows_cnt; i++) {
		pie_cleanup(&flows[i]);
	}
	si->si_extra = NULL;
	return 0;
}