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
struct TYPE_5__ {int mc_flags; int /*<<< orphan*/  mc_fpregs; } ;
struct TYPE_4__ {TYPE_2__ uc_mcontext; } ;
typedef  TYPE_1__ ucontext_t ;
struct fpreg {int dummy; } ;
typedef  TYPE_2__ mcontext_t ;

/* Variables and functions */
 int _MC_FP_VALID ; 
 int /*<<< orphan*/  memcpy (struct fpreg*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct fpreg*,int /*<<< orphan*/ ,int) ; 

void
pt_ucontext_to_fpreg(const ucontext_t *uc, struct fpreg *r)
{
	const mcontext_t *mc = &uc->uc_mcontext;

	if (mc->mc_flags & _MC_FP_VALID)
		memcpy(r, &mc->mc_fpregs, sizeof(*r));
	else
		memset(r, 0, sizeof(*r));

}