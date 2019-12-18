#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int u32 ;
struct TYPE_11__ {void* size; void* addr; } ;
struct sym_pmc {TYPE_4__ sg; void* ret; } ;
typedef  int /*<<< orphan*/  hcb_p ;
typedef  TYPE_5__* ccb_p ;
struct TYPE_8__ {int goalp; } ;
struct TYPE_10__ {TYPE_2__* data; struct sym_pmc pm1; struct sym_pmc pm0; TYPE_1__ head; } ;
struct TYPE_12__ {int host_flags; TYPE_3__ phys; } ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int HF_ACT_PM ; 
 int HF_DP_SAVED ; 
 int /*<<< orphan*/  HF_PRT ; 
 int HF_SENSE ; 
 int INB (int /*<<< orphan*/ ) ; 
 int INL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL_DSP (int) ; 
 int SCRIPTA_BA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SCRIPTB_BA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SYM_CONF_MAX_SG ; 
 int /*<<< orphan*/  clrack ; 
 void* cpu_to_scr (int) ; 
 int /*<<< orphan*/  msg_bad ; 
 int /*<<< orphan*/  nc_temp ; 
 int /*<<< orphan*/  pm0_data ; 
 int /*<<< orphan*/  pm1_data ; 
 int scr_to_cpu (int /*<<< orphan*/ ) ; 
 int sym_evaluate_dp (int /*<<< orphan*/ ,TYPE_5__*,int,int*) ; 

__attribute__((used)) static void sym_modify_dp(hcb_p np, ccb_p cp, int ofs)
{
	int dp_ofs	= ofs;
	u32	dp_scr	= INL (nc_temp);
	u32	dp_ret;
	u32	tmp;
	u_char	hflags;
	int	dp_sg;
	struct	sym_pmc *pm;

	/*
	 *  Not supported for auto-sense.
	 */
	if (cp->host_flags & HF_SENSE)
		goto out_reject;

	/*
	 *  Apply our alchemy:) (see comments in sym_evaluate_dp()),
	 *  to the resulted data pointer.
	 */
	dp_sg = sym_evaluate_dp(np, cp, dp_scr, &dp_ofs);
	if (dp_sg < 0)
		goto out_reject;

	/*
	 *  And our alchemy:) allows to easily calculate the data
	 *  script address we want to return for the next data phase.
	 */
	dp_ret = cpu_to_scr(cp->phys.head.goalp);
	dp_ret = dp_ret - 8 - (SYM_CONF_MAX_SG - dp_sg) * (2*4);

	/*
	 *  If offset / scatter entry is zero we donnot need
	 *  a context for the new current data pointer.
	 */
	if (dp_ofs == 0) {
		dp_scr = dp_ret;
		goto out_ok;
	}

	/*
	 *  Get a context for the new current data pointer.
	 */
	hflags = INB (HF_PRT);

	if (hflags & HF_DP_SAVED)
		hflags ^= HF_ACT_PM;

	if (!(hflags & HF_ACT_PM)) {
		pm  = &cp->phys.pm0;
		dp_scr = SCRIPTA_BA (np, pm0_data);
	}
	else {
		pm = &cp->phys.pm1;
		dp_scr = SCRIPTA_BA (np, pm1_data);
	}

	hflags &= ~(HF_DP_SAVED);

	OUTB (HF_PRT, hflags);

	/*
	 *  Set up the new current data pointer.
	 *  ofs < 0 there, and for the next data phase, we
	 *  want to transfer part of the data of the sg entry
	 *  corresponding to index dp_sg-1 prior to returning
	 *  to the main data script.
	 */
	pm->ret = cpu_to_scr(dp_ret);
	tmp  = scr_to_cpu(cp->phys.data[dp_sg-1].addr);
	tmp += scr_to_cpu(cp->phys.data[dp_sg-1].size) + dp_ofs;
	pm->sg.addr = cpu_to_scr(tmp);
	pm->sg.size = cpu_to_scr(-dp_ofs);

out_ok:
	OUTL (nc_temp, dp_scr);
	OUTL_DSP (SCRIPTA_BA (np, clrack));
	return;

out_reject:
	OUTL_DSP (SCRIPTB_BA (np, msg_bad));
}