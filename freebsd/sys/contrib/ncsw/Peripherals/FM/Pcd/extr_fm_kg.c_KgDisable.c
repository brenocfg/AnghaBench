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
struct TYPE_5__ {int /*<<< orphan*/  h_Fm; TYPE_1__* p_FmPcdKg; } ;
typedef  TYPE_2__ t_FmPcd ;
struct fman_kg_regs {int dummy; } ;
struct TYPE_4__ {struct fman_kg_regs* p_FmPcdKgRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmIsMaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fman_kg_disable (struct fman_kg_regs*) ; 

void KgDisable(t_FmPcd *p_FmPcd)
{
    struct fman_kg_regs *p_Regs = p_FmPcd->p_FmPcdKg->p_FmPcdKgRegs;

    ASSERT_COND(FmIsMaster(p_FmPcd->h_Fm));
    fman_kg_disable(p_Regs);
}