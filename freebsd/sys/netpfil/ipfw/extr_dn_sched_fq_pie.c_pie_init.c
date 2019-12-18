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
struct pie_status {int one_third_q_size; int /*<<< orphan*/  lock_mtx; int /*<<< orphan*/  aqm_pie_callout; struct dn_aqm_pie_parms* parms; } ;
struct TYPE_4__ {int limit; int flows_cnt; } ;
struct fq_pie_schk {TYPE_2__ cfg; } ;
struct fq_pie_flow {TYPE_1__* psi_extra; struct pie_status pst; } ;
struct dn_aqm_pie_parms {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_active_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLOUT_RETURNUNLOCKED ; 
 int /*<<< orphan*/  D (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pie_init(struct fq_pie_flow *q, struct fq_pie_schk *fqpie_schk)
{
	struct pie_status *pst=&q->pst;
	struct dn_aqm_pie_parms *pprms = pst->parms;

	int err = 0;
	if (!pprms){
		D("AQM_PIE is not configured");
		err = EINVAL;
	} else {
		q->psi_extra->nr_active_q++;

		/* For speed optimization, we caculate 1/3 queue size once here */
		// XXX limit divided by number of queues divided by 3 ??? 
		pst->one_third_q_size = (fqpie_schk->cfg.limit / 
			fqpie_schk->cfg.flows_cnt) / 3;

		mtx_init(&pst->lock_mtx, "mtx_pie", NULL, MTX_DEF);
		callout_init_mtx(&pst->aqm_pie_callout, &pst->lock_mtx,
			CALLOUT_RETURNUNLOCKED);
	}

	return err;
}