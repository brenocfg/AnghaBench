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
struct TYPE_3__ {int /*<<< orphan*/  addr_ce; } ;
struct qm_mc {int /*<<< orphan*/  state; void* rridx; void* vbit; TYPE_2__* cr; void* rr; } ;
struct qm_portal {TYPE_1__ addr; struct qm_mc mc; } ;
struct TYPE_4__ {int __dont_write_directly__verb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_CR ; 
 int /*<<< orphan*/  CL_RR0 ; 
 int /*<<< orphan*/  ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_BUSY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  QM_BIND_MC ; 
 int QM_MCC_VERB_VBIT ; 
 scalar_t__ __qm_portal_bind (struct qm_portal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_idle ; 
 void* ptr_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ t_Error qm_mc_init(struct qm_portal *portal)
{
    register struct qm_mc *mc = &portal->mc;
    if (__qm_portal_bind(portal, QM_BIND_MC))
        return ERROR_CODE(E_BUSY);
    mc->cr = ptr_ADD(portal->addr.addr_ce, CL_CR);
    mc->rr = ptr_ADD(portal->addr.addr_ce, CL_RR0);
    mc->rridx = (uint8_t)((mc->cr->__dont_write_directly__verb & QM_MCC_VERB_VBIT) ?
            0 : 1);
    mc->vbit = (uint8_t)(mc->rridx ? QM_MCC_VERB_VBIT : 0);
#ifdef QM_CHECKING
    mc->state = mc_idle;
#endif /* QM_CHECKING */
    return E_OK;
}