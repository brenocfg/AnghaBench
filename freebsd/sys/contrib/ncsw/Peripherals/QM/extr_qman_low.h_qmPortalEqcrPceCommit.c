#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct qm_eqcr {scalar_t__ pmode; int vbit; scalar_t__ busy; TYPE_1__* cursor; int /*<<< orphan*/  available; } ;
struct qm_portal {struct qm_eqcr eqcr; } ;
struct TYPE_3__ {int __dont_write_directly__verb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  EQCR_COMMIT_CHECKS (struct qm_eqcr*) ; 
 int /*<<< orphan*/  EQCR_INC (struct qm_eqcr*) ; 
 int /*<<< orphan*/  EQCR_PI ; 
 int /*<<< orphan*/  EQCR_PTR2IDX (TYPE_1__*) ; 
 int /*<<< orphan*/  dcbf_64 (TYPE_1__*) ; 
 scalar_t__ e_QmPortalPCE ; 
 int /*<<< orphan*/  qm_cl_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static __inline__ void qmPortalEqcrPceCommit(struct qm_portal *portal, uint8_t myverb)
{
    register struct qm_eqcr *eqcr = &portal->eqcr;
#ifdef QM_CHECKING
    EQCR_COMMIT_CHECKS(eqcr);
    ASSERT_COND(eqcr->pmode == e_QmPortalPCE);
#endif /* QM_CHECKING */
    eqcr->cursor->__dont_write_directly__verb = (uint8_t)(myverb | eqcr->vbit);
    EQCR_INC(eqcr);
    eqcr->available--;
    dcbf_64(eqcr->cursor);
    wmb();
    qm_cl_out(EQCR_PI, EQCR_PTR2IDX(eqcr->cursor));
#ifdef QM_CHECKING
    eqcr->busy = 0;
#endif /* QM_CHECKING */
}