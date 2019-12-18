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
struct TYPE_7__ {scalar_t__ qdelay_ref; scalar_t__ tupdate; scalar_t__ max_burst; scalar_t__ max_ecnth; scalar_t__ alpha; scalar_t__ beta; scalar_t__ flags; } ;
struct dn_sch_fq_pie_parms {scalar_t__ quantum; scalar_t__ limit; scalar_t__ flows_cnt; TYPE_3__ pcfg; } ;
struct fq_pie_schk {struct dn_sch_fq_pie_parms cfg; } ;
struct dn_schk {scalar_t__ cfg; } ;
struct TYPE_5__ {int len; scalar_t__ subtype; } ;
struct dn_extra_parms {scalar_t__* par; TYPE_1__ oid; } ;
struct TYPE_6__ {scalar_t__ qdelay_ref; scalar_t__ tupdate; scalar_t__ max_burst; scalar_t__ max_ecnth; scalar_t__ alpha; scalar_t__ beta; } ;
struct TYPE_8__ {scalar_t__ quantum; scalar_t__ limit; scalar_t__ flows_cnt; TYPE_2__ pcfg; } ;

/* Variables and functions */
 int AQM_TIME_1S ; 
 void* BOUND_VAR (scalar_t__,int,int) ; 
 int /*<<< orphan*/  D (char*) ; 
 scalar_t__ DN_SCH_PARAMS ; 
 int PIE_SCALE ; 
 TYPE_4__ fq_pie_sysctl ; 

__attribute__((used)) static int
fq_pie_config(struct dn_schk *_schk)
{
	struct fq_pie_schk *schk;
	struct dn_extra_parms *ep;
	struct dn_sch_fq_pie_parms *fqp_cfg;
	
	schk = (struct fq_pie_schk *)(_schk+1);
	ep = (struct dn_extra_parms *) _schk->cfg;

	/* par array contains fq_pie configuration as follow
	 * PIE: 0- qdelay_ref,1- tupdate, 2- max_burst
	 * 3- max_ecnth, 4- alpha, 5- beta, 6- flags
	 * FQ_PIE: 7- quantum, 8- limit, 9- flows
	 */
	if (ep && ep->oid.len ==sizeof(*ep) &&
		ep->oid.subtype == DN_SCH_PARAMS) {

		fqp_cfg = &schk->cfg;
		if (ep->par[0] < 0)
			fqp_cfg->pcfg.qdelay_ref = fq_pie_sysctl.pcfg.qdelay_ref;
		else
			fqp_cfg->pcfg.qdelay_ref = ep->par[0];
		if (ep->par[1] < 0)
			fqp_cfg->pcfg.tupdate = fq_pie_sysctl.pcfg.tupdate;
		else
			fqp_cfg->pcfg.tupdate = ep->par[1];
		if (ep->par[2] < 0)
			fqp_cfg->pcfg.max_burst = fq_pie_sysctl.pcfg.max_burst;
		else
			fqp_cfg->pcfg.max_burst = ep->par[2];
		if (ep->par[3] < 0)
			fqp_cfg->pcfg.max_ecnth = fq_pie_sysctl.pcfg.max_ecnth;
		else
			fqp_cfg->pcfg.max_ecnth = ep->par[3];
		if (ep->par[4] < 0)
			fqp_cfg->pcfg.alpha = fq_pie_sysctl.pcfg.alpha;
		else
			fqp_cfg->pcfg.alpha = ep->par[4];
		if (ep->par[5] < 0)
			fqp_cfg->pcfg.beta = fq_pie_sysctl.pcfg.beta;
		else
			fqp_cfg->pcfg.beta = ep->par[5];
		if (ep->par[6] < 0)
			fqp_cfg->pcfg.flags = 0;
		else
			fqp_cfg->pcfg.flags = ep->par[6];

		/* FQ configurations */
		if (ep->par[7] < 0)
			fqp_cfg->quantum = fq_pie_sysctl.quantum;
		else
			fqp_cfg->quantum = ep->par[7];
		if (ep->par[8] < 0)
			fqp_cfg->limit = fq_pie_sysctl.limit;
		else
			fqp_cfg->limit = ep->par[8];
		if (ep->par[9] < 0)
			fqp_cfg->flows_cnt = fq_pie_sysctl.flows_cnt;
		else
			fqp_cfg->flows_cnt = ep->par[9];

		/* Bound the configurations */
		fqp_cfg->pcfg.qdelay_ref = BOUND_VAR(fqp_cfg->pcfg.qdelay_ref,
			1, 5 * AQM_TIME_1S);
		fqp_cfg->pcfg.tupdate = BOUND_VAR(fqp_cfg->pcfg.tupdate,
			1, 5 * AQM_TIME_1S);
		fqp_cfg->pcfg.max_burst = BOUND_VAR(fqp_cfg->pcfg.max_burst,
			0, 5 * AQM_TIME_1S);
		fqp_cfg->pcfg.max_ecnth = BOUND_VAR(fqp_cfg->pcfg.max_ecnth,
			0, PIE_SCALE);
		fqp_cfg->pcfg.alpha = BOUND_VAR(fqp_cfg->pcfg.alpha, 0, 7 * PIE_SCALE);
		fqp_cfg->pcfg.beta = BOUND_VAR(fqp_cfg->pcfg.beta, 0, 7 * PIE_SCALE);

		fqp_cfg->quantum = BOUND_VAR(fqp_cfg->quantum,1,9000);
		fqp_cfg->limit= BOUND_VAR(fqp_cfg->limit,1,20480);
		fqp_cfg->flows_cnt= BOUND_VAR(fqp_cfg->flows_cnt,1,65536);
	}
	else {
		D("Wrong parameters for fq_pie scheduler");
		return 1;
	}

	return 0;
}