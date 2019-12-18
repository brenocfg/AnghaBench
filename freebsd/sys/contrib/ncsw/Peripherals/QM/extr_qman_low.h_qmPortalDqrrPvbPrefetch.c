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
struct qm_dqrr {scalar_t__ pmode; int flags; int /*<<< orphan*/  pi; int /*<<< orphan*/  ring; } ;
struct qm_portal {struct qm_dqrr dqrr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int QM_DQRR_FLAG_RE ; 
 int /*<<< orphan*/  dcbit_ro (int /*<<< orphan*/ ) ; 
 scalar_t__ e_QmPortalPVB ; 
 int /*<<< orphan*/  ptr_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_cl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void qmPortalDqrrPvbPrefetch(struct qm_portal *portal)
{
    register struct qm_dqrr *dqrr = &portal->dqrr;
#ifdef QM_CHECKING
    ASSERT_COND(dqrr->pmode == e_QmPortalPVB);
    /* If ring entries get stashed, don't invalidate/prefetch */
    if (!(dqrr->flags & QM_DQRR_FLAG_RE))
#endif /*QM_CHECKING */
        dcbit_ro(ptr_ADD(dqrr->ring, qm_cl(dqrr->pi)));
}