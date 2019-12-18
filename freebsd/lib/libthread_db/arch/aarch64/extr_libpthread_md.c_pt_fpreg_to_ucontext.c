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
struct TYPE_5__ {int /*<<< orphan*/  mc_flags; int /*<<< orphan*/  mc_fpregs; } ;
struct TYPE_4__ {TYPE_2__ uc_mcontext; } ;
typedef  TYPE_1__ ucontext_t ;
struct fpreg {int dummy; } ;
typedef  TYPE_2__ mcontext_t ;

/* Variables and functions */
 int /*<<< orphan*/  _MC_FP_VALID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct fpreg const*,int) ; 

void
pt_fpreg_to_ucontext(const struct fpreg *r, ucontext_t *uc)
{
	mcontext_t *mc = &uc->uc_mcontext;

	memcpy(&mc->mc_fpregs, r, sizeof(*r));
	mc->mc_flags |= _MC_FP_VALID;
}