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
typedef  int uint64_t ;
struct pie_status {int drop_prob; int current_qdelay; int avg_dq_time; int qdelay_old; int sflags; scalar_t__ burst_allowance; int /*<<< orphan*/  lock_mtx; int /*<<< orphan*/  aqm_pie_callout; struct dn_aqm_pie_parms* parms; } ;
struct TYPE_2__ {scalar_t__ len_bytes; } ;
struct fq_pie_flow {TYPE_1__ stats; struct pie_status pst; } ;
struct dn_aqm_pie_parms {int flags; scalar_t__ tupdate; scalar_t__ beta; scalar_t__ qdelay_ref; scalar_t__ alpha; } ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  aqm_time_t ;

/* Variables and functions */
 int AQM_TIME_1S ; 
 int /*<<< orphan*/  AQM_UNOW ; 
 int /*<<< orphan*/  D (char*) ; 
 int PIE_ACTIVE ; 
 int PIE_CAPDROP_ENABLED ; 
 int PIE_DEPRATEEST_ENABLED ; 
 int PIE_DQ_THRESHOLD_BITS ; 
 int PIE_FIX_POINT_BITS ; 
 int PIE_MAX_PROB ; 
 int SBT_1US ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void (*) (void*),struct fq_pie_flow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fq_calculate_drop_prob(void *x)
{
	struct fq_pie_flow *q = (struct fq_pie_flow *) x;
	struct pie_status *pst = &q->pst;
	struct dn_aqm_pie_parms *pprms; 
	int64_t p, prob, oldprob;
	aqm_time_t now;
	int p_isneg;

	now = AQM_UNOW;
	pprms = pst->parms;
	prob = pst->drop_prob;

	/* calculate current qdelay using DRE method.
	 * If TS is used and no data in the queue, reset current_qdelay
	 * as it stays at last value during dequeue process.
	*/
	if (pprms->flags & PIE_DEPRATEEST_ENABLED)
		pst->current_qdelay = ((uint64_t)q->stats.len_bytes  * pst->avg_dq_time)
			>> PIE_DQ_THRESHOLD_BITS;
	else
		if (!q->stats.len_bytes)
			pst->current_qdelay = 0;

	/* calculate drop probability */
	p = (int64_t)pprms->alpha * 
		((int64_t)pst->current_qdelay - (int64_t)pprms->qdelay_ref); 
	p +=(int64_t) pprms->beta * 
		((int64_t)pst->current_qdelay - (int64_t)pst->qdelay_old); 

	/* take absolute value so right shift result is well defined */
	p_isneg = p < 0;
	if (p_isneg) {
		p = -p;
	}
		
	/* We PIE_MAX_PROB shift by 12-bits to increase the division precision  */
	p *= (PIE_MAX_PROB << 12) / AQM_TIME_1S;

	/* auto-tune drop probability */
	if (prob < (PIE_MAX_PROB / 1000000)) /* 0.000001 */
		p >>= 11 + PIE_FIX_POINT_BITS + 12;
	else if (prob < (PIE_MAX_PROB / 100000)) /* 0.00001 */
		p >>= 9 + PIE_FIX_POINT_BITS + 12;
	else if (prob < (PIE_MAX_PROB / 10000)) /* 0.0001 */
		p >>= 7 + PIE_FIX_POINT_BITS + 12;
	else if (prob < (PIE_MAX_PROB / 1000)) /* 0.001 */
		p >>= 5 + PIE_FIX_POINT_BITS + 12;
	else if (prob < (PIE_MAX_PROB / 100)) /* 0.01 */
		p >>= 3 + PIE_FIX_POINT_BITS + 12;
	else if (prob < (PIE_MAX_PROB / 10)) /* 0.1 */
		p >>= 1 + PIE_FIX_POINT_BITS + 12;
	else
		p >>= PIE_FIX_POINT_BITS + 12;

	oldprob = prob;

	if (p_isneg) {
		prob = prob - p;

		/* check for multiplication underflow */
		if (prob > oldprob) {
			prob= 0;
			D("underflow");
		}
	} else {
		/* Cap Drop adjustment */
		if ((pprms->flags & PIE_CAPDROP_ENABLED) &&
		    prob >= PIE_MAX_PROB / 10 &&
		    p > PIE_MAX_PROB / 50 ) {
			p = PIE_MAX_PROB / 50;
		}

		prob = prob + p;

		/* check for multiplication overflow */
		if (prob<oldprob) {
			D("overflow");
			prob= PIE_MAX_PROB;
		}
	}

	/*
	 * decay the drop probability exponentially
	 * and restrict it to range 0 to PIE_MAX_PROB
	 */
	if (prob < 0) {
		prob = 0;
	} else {
		if (pst->current_qdelay == 0 && pst->qdelay_old == 0) {
			/* 0.98 ~= 1- 1/64 */
			prob = prob - (prob >> 6); 
		}

		if (prob > PIE_MAX_PROB) {
			prob = PIE_MAX_PROB;
		}
	}

	pst->drop_prob = prob;
	
	/* store current delay value */
	pst->qdelay_old = pst->current_qdelay;

	/* update burst allowance */
	if ((pst->sflags & PIE_ACTIVE) && pst->burst_allowance) {
		if (pst->burst_allowance > pprms->tupdate)
			pst->burst_allowance -= pprms->tupdate;
		else 
			pst->burst_allowance = 0;
	}

	if (pst->sflags & PIE_ACTIVE)
	callout_reset_sbt(&pst->aqm_pie_callout,
		(uint64_t)pprms->tupdate * SBT_1US,
		0, fq_calculate_drop_prob, q, 0);

	mtx_unlock(&pst->lock_mtx);
}