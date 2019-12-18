#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_4__ {int /*<<< orphan*/  addr_ce; } ;
struct bm_mc {int /*<<< orphan*/  state; void* rridx; void* vbit; TYPE_1__* cr; void* rr; } ;
struct bm_portal {TYPE_2__ addr; struct bm_mc mc; } ;
struct TYPE_3__ {int __dont_write_directly__verb; } ;

/* Variables and functions */
 int BM_MCC_VERB_VBIT ; 
 int /*<<< orphan*/  CL_CR ; 
 int /*<<< orphan*/  CL_RR0 ; 
 int /*<<< orphan*/  mc_idle ; 
 void* ptr_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

t_Error bm_mc_init(struct bm_portal *portal)
{
    register struct bm_mc *mc = &portal->mc;
    mc->cr = ptr_ADD(portal->addr.addr_ce, CL_CR);
    mc->rr = ptr_ADD(portal->addr.addr_ce, CL_RR0);
    mc->rridx = (uint8_t)((mc->cr->__dont_write_directly__verb & BM_MCC_VERB_VBIT) ?
            0 : 1);
    mc->vbit = (uint8_t)(mc->rridx ? BM_MCC_VERB_VBIT : 0);
#ifdef BM_CHECKING
    mc->state = mc_idle;
#endif /* BM_CHECKING */
    return 0;
}