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
struct TYPE_4__ {scalar_t__ mc_fpformat; } ;
struct TYPE_5__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;

/* Variables and functions */
 scalar_t__ _MC_FPFMT_XMM ; 
 int /*<<< orphan*/  getcontext (TYPE_2__*) ; 
 int has_xmm_regs ; 

void
pt_md_init(void)
{
	ucontext_t uc;

	getcontext(&uc);
	if (uc.uc_mcontext.mc_fpformat == _MC_FPFMT_XMM)
	    has_xmm_regs = 1;
}