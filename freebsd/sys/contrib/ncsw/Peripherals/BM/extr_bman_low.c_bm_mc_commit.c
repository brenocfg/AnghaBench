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
typedef  int uint8_t ;
struct bm_mc {scalar_t__ state; int vbit; scalar_t__ rridx; scalar_t__ rr; TYPE_1__* cr; } ;
struct bm_portal {struct bm_mc mc; } ;
struct TYPE_2__ {int __dont_write_directly__verb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  dcbf_64 (TYPE_1__*) ; 
 int /*<<< orphan*/  dcbit_ro (scalar_t__) ; 
 scalar_t__ mc_hw ; 
 scalar_t__ mc_user ; 
 int /*<<< orphan*/  rmb () ; 

void bm_mc_commit(struct bm_portal *portal, uint8_t myverb)
{
    register struct bm_mc *mc = &portal->mc;
    ASSERT_COND(mc->state == mc_user);
    rmb();
    mc->cr->__dont_write_directly__verb = (uint8_t)(myverb | mc->vbit);
    dcbf_64(mc->cr);
    dcbit_ro(mc->rr + mc->rridx);
#ifdef BM_CHECKING
    mc->state = mc_hw;
#endif /* BM_CHECKING */
}