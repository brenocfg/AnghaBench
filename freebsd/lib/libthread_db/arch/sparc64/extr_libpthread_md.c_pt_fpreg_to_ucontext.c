#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  _mc_fprs; int /*<<< orphan*/  _mc_gsr; int /*<<< orphan*/  _mc_fsr; int /*<<< orphan*/  mc_fp; } ;
struct TYPE_4__ {TYPE_2__ uc_mcontext; } ;
typedef  TYPE_1__ ucontext_t ;
struct fpreg {int /*<<< orphan*/  fr_gsr; int /*<<< orphan*/  fr_fsr; int /*<<< orphan*/  fr_regs; } ;
typedef  TYPE_2__ mcontext_t ;

/* Variables and functions */
 int /*<<< orphan*/  FPRS_FEF ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pt_fpreg_to_ucontext(const struct fpreg* r, ucontext_t *uc)
{
	mcontext_t *mc = &uc->uc_mcontext;

	memcpy(mc->mc_fp, r->fr_regs, MIN(sizeof(mc->mc_fp),
	    sizeof(r->fr_regs)));
	mc->_mc_fsr = r->fr_fsr;
	mc->_mc_gsr = r->fr_gsr;
	mc->_mc_fprs |= FPRS_FEF;
}