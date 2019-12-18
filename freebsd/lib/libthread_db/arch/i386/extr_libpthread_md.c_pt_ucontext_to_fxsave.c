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
struct TYPE_4__ {int /*<<< orphan*/  mc_fpstate; } ;
struct TYPE_5__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
struct savexmm {int dummy; } ;

/* Variables and functions */
 scalar_t__ has_xmm_regs ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

void
pt_ucontext_to_fxsave(const ucontext_t *uc, char *r)
{
	if (has_xmm_regs)
		memcpy(r, &uc->uc_mcontext.mc_fpstate, sizeof(struct savexmm));
}