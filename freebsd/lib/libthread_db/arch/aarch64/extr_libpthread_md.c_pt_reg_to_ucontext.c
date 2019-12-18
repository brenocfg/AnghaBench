#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  gp_spsr; int /*<<< orphan*/  gp_elr; int /*<<< orphan*/  gp_lr; int /*<<< orphan*/  gp_sp; int /*<<< orphan*/  gp_x; } ;
struct TYPE_7__ {TYPE_1__ mc_gpregs; } ;
struct TYPE_6__ {TYPE_3__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
struct reg {int /*<<< orphan*/  spsr; int /*<<< orphan*/  elr; int /*<<< orphan*/  lr; int /*<<< orphan*/  sp; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ mcontext_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
pt_reg_to_ucontext(const struct reg *r, ucontext_t *uc)
{
	mcontext_t *mc = &uc->uc_mcontext;

	memcpy(mc->mc_gpregs.gp_x, r->x, sizeof(mc->mc_gpregs.gp_x));
	mc->mc_gpregs.gp_sp = r->sp;
	mc->mc_gpregs.gp_lr = r->lr;
	mc->mc_gpregs.gp_elr = r->elr;
	mc->mc_gpregs.gp_spsr = r->spsr;
}