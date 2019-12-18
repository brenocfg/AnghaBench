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
typedef  int uint64_t ;
struct pie_status {int sflags; int /*<<< orphan*/  lock_mtx; int /*<<< orphan*/  aqm_pie_callout; int /*<<< orphan*/  measurement_start; scalar_t__ avg_dq_time; scalar_t__ dq_count; scalar_t__ accu_prob; int /*<<< orphan*/  burst_allowance; scalar_t__ qdelay_old; scalar_t__ drop_prob; struct dn_aqm_pie_parms* parms; } ;
struct fq_pie_flow {struct pie_status pst; } ;
struct dn_aqm_pie_parms {scalar_t__ tupdate; int /*<<< orphan*/  max_burst; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQM_UNOW ; 
 int PIE_ACTIVE ; 
 int PIE_INMEASUREMENT ; 
 int SBT_1US ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fq_pie_flow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fq_calculate_drop_prob ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) __inline static void
fq_activate_pie(struct fq_pie_flow *q)
{ 
	struct pie_status *pst = &q->pst;
	struct dn_aqm_pie_parms *pprms;

	mtx_lock(&pst->lock_mtx);
	pprms = pst->parms;

	pprms = pst->parms;
	pst->drop_prob = 0;
	pst->qdelay_old = 0;
	pst->burst_allowance = pprms->max_burst;
	pst->accu_prob = 0;
	pst->dq_count = 0;
	pst->avg_dq_time = 0;
	pst->sflags = PIE_INMEASUREMENT | PIE_ACTIVE;
	pst->measurement_start = AQM_UNOW;
	
	callout_reset_sbt(&pst->aqm_pie_callout,
		(uint64_t)pprms->tupdate * SBT_1US,
		0, fq_calculate_drop_prob, q, 0);

	mtx_unlock(&pst->lock_mtx);
}