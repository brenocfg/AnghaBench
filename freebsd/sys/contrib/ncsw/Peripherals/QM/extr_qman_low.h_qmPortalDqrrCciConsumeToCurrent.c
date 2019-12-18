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
struct qm_dqrr {scalar_t__ cmode; int /*<<< orphan*/  ci; int /*<<< orphan*/  cursor; } ;
struct qm_portal {struct qm_dqrr dqrr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  DQRR_CI_CINH ; 
 int /*<<< orphan*/  DQRR_PTR2IDX (int /*<<< orphan*/ ) ; 
 scalar_t__ e_QmPortalDqrrCCI ; 
 int /*<<< orphan*/  qm_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void qmPortalDqrrCciConsumeToCurrent(struct qm_portal *portal)
{
    register struct qm_dqrr *dqrr = &portal->dqrr;
#ifdef QM_CHECKING
    ASSERT_COND(dqrr->cmode == e_QmPortalDqrrCCI);
#endif /* QM_CHECKING */
    dqrr->ci = DQRR_PTR2IDX(dqrr->cursor);
    qm_out(DQRR_CI_CINH, dqrr->ci);
}