#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct envxmm {int /*<<< orphan*/  en_mxcsr_mask; int /*<<< orphan*/  en_mxcsr; int /*<<< orphan*/  en_rdp; int /*<<< orphan*/  en_rip; int /*<<< orphan*/  en_opcode; int /*<<< orphan*/  en_tw; int /*<<< orphan*/  en_sw; int /*<<< orphan*/  en_cw; } ;
struct savefpu {TYPE_3__* sv_xmm; TYPE_2__* sv_fp; struct envxmm sv_env; } ;
struct fpreg {int /*<<< orphan*/ * fpr_xacc; int /*<<< orphan*/ * fpr_acc; int /*<<< orphan*/  fpr_env; } ;
struct TYPE_6__ {int /*<<< orphan*/  xmm_bytes; } ;
struct TYPE_4__ {int /*<<< orphan*/  fp_bytes; } ;
struct TYPE_5__ {TYPE_1__ fp_acc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct fpreg*,int) ; 

__attribute__((used)) static void
fill_fpregs_xmm(struct savefpu *sv_xmm, struct fpreg *fpregs)
{
	struct envxmm *penv_fpreg = (struct envxmm *)&fpregs->fpr_env;
	struct envxmm *penv_xmm = &sv_xmm->sv_env;
	int i;

	/* pcb -> fpregs */
	bzero(fpregs, sizeof(*fpregs));

	/* FPU control/status */
	penv_fpreg->en_cw = penv_xmm->en_cw;
	penv_fpreg->en_sw = penv_xmm->en_sw;
	penv_fpreg->en_tw = penv_xmm->en_tw;
	penv_fpreg->en_opcode = penv_xmm->en_opcode;
	penv_fpreg->en_rip = penv_xmm->en_rip;
	penv_fpreg->en_rdp = penv_xmm->en_rdp;
	penv_fpreg->en_mxcsr = penv_xmm->en_mxcsr;
	penv_fpreg->en_mxcsr_mask = penv_xmm->en_mxcsr_mask;

	/* FPU registers */
	for (i = 0; i < 8; ++i)
		bcopy(sv_xmm->sv_fp[i].fp_acc.fp_bytes, fpregs->fpr_acc[i], 10);

	/* SSE registers */
	for (i = 0; i < 16; ++i)
		bcopy(sv_xmm->sv_xmm[i].xmm_bytes, fpregs->fpr_xacc[i], 16);
}