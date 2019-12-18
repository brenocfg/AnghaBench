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
struct thread {int dummy; } ;
struct envxmm {int en_tw; int /*<<< orphan*/  en_rdp; int /*<<< orphan*/  en_opcode; int /*<<< orphan*/  en_rip; int /*<<< orphan*/  en_sw; int /*<<< orphan*/  en_cw; } ;
struct savefpu {TYPE_1__* sv_fp; struct envxmm sv_env; } ;
struct env87 {int en_tw; int /*<<< orphan*/  en_foo; int /*<<< orphan*/  en_opcode; int /*<<< orphan*/  en_fip; int /*<<< orphan*/  en_sw; int /*<<< orphan*/  en_cw; } ;
struct save87 {int /*<<< orphan*/ * sv_ac; struct env87 sv_env; } ;
struct fpreg32 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fp_acc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fpuuserinited (struct thread*) ; 
 struct savefpu* get_pcb_user_save_td (struct thread*) ; 

int
set_fpregs32(struct thread *td, struct fpreg32 *regs)
{
	struct save87 *sv_87 = (struct save87 *)regs;
	struct env87 *penv_87 = &sv_87->sv_env;
	struct savefpu *sv_fpu = get_pcb_user_save_td(td);
	struct envxmm *penv_xmm = &sv_fpu->sv_env;
	int i;

	/* FPU control/status */
	penv_xmm->en_cw = penv_87->en_cw;
	penv_xmm->en_sw = penv_87->en_sw;
	penv_xmm->en_rip = penv_87->en_fip;
	/* penv_87->en_fcs and en_fos ignored, see above */
	penv_xmm->en_opcode = penv_87->en_opcode;
	penv_xmm->en_rdp = penv_87->en_foo;

	/* FPU registers and tags */
	penv_xmm->en_tw = 0;
	for (i = 0; i < 8; ++i) {
		sv_fpu->sv_fp[i].fp_acc = sv_87->sv_ac[i];
		if ((penv_87->en_tw & (3 << i * 2)) != (3 << i * 2))
			penv_xmm->en_tw |= 1 << i;
	}

	for (i = 8; i < 16; ++i)
		bzero(&sv_fpu->sv_fp[i].fp_acc, sizeof(sv_fpu->sv_fp[i].fp_acc));
	fpuuserinited(td);

	return (0);
}