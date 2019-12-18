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
struct qm_eqcr {scalar_t__ cmode; } ;
struct qm_portal {struct qm_eqcr eqcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  EQCR_CI ; 
 scalar_t__ e_QmPortalEqcrCCE ; 
 int /*<<< orphan*/  qm_cl_touch_ro (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void qmPortalEqcrCcePrefetch(struct qm_portal *portal)
{
#ifdef QM_CHECKING
    register struct qm_eqcr *eqcr = &portal->eqcr;
    ASSERT_COND(eqcr->cmode == e_QmPortalEqcrCCE);
#endif /* QM_CHECKING */
    qm_cl_touch_ro(EQCR_CI);
}