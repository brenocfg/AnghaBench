#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qm_eqcr {scalar_t__ busy; } ;
struct qm_portal {struct qm_eqcr eqcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (scalar_t__) ; 
 int /*<<< orphan*/  UNUSED (struct qm_portal*) ; 

__attribute__((used)) static __inline__ void qm_eqcr_abort(struct qm_portal *portal)
{
#ifdef QM_CHECKING
    register struct qm_eqcr *eqcr = &portal->eqcr;
    ASSERT_COND(eqcr->busy);
    eqcr->busy = 0;
#else
    UNUSED(portal);
#endif /* QM_CHECKING */
}