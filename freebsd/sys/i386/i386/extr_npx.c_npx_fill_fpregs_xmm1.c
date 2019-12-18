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
struct envxmm {int en_tw; int /*<<< orphan*/  en_fos; int /*<<< orphan*/  en_foo; int /*<<< orphan*/  en_opcode; int /*<<< orphan*/  en_fcs; int /*<<< orphan*/  en_fip; int /*<<< orphan*/  en_sw; int /*<<< orphan*/  en_cw; } ;
struct savexmm {TYPE_1__* sv_fp; struct envxmm sv_env; } ;
struct env87 {int en_tw; int /*<<< orphan*/  en_fos; int /*<<< orphan*/  en_foo; int /*<<< orphan*/  en_opcode; int /*<<< orphan*/  en_fcs; int /*<<< orphan*/  en_fip; int /*<<< orphan*/  en_sw; int /*<<< orphan*/  en_cw; } ;
struct save87 {int /*<<< orphan*/ * sv_ac; struct env87 sv_env; } ;
struct TYPE_2__ {int /*<<< orphan*/  fp_acc; } ;

/* Variables and functions */

__attribute__((used)) static void
npx_fill_fpregs_xmm1(struct savexmm *sv_xmm, struct save87 *sv_87)
{
	struct env87 *penv_87;
	struct envxmm *penv_xmm;
	int i;

	penv_87 = &sv_87->sv_env;
	penv_xmm = &sv_xmm->sv_env;

	/* FPU control/status */
	penv_87->en_cw = penv_xmm->en_cw;
	penv_87->en_sw = penv_xmm->en_sw;
	penv_87->en_fip = penv_xmm->en_fip;
	penv_87->en_fcs = penv_xmm->en_fcs;
	penv_87->en_opcode = penv_xmm->en_opcode;
	penv_87->en_foo = penv_xmm->en_foo;
	penv_87->en_fos = penv_xmm->en_fos;

	/* FPU registers and tags */
	penv_87->en_tw = 0xffff;
	for (i = 0; i < 8; ++i) {
		sv_87->sv_ac[i] = sv_xmm->sv_fp[i].fp_acc;
		if ((penv_xmm->en_tw & (1 << i)) != 0)
			/* zero and special are set as valid */
			penv_87->en_tw &= ~(3 << i * 2);
	}
}