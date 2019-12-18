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
typedef  scalar_t__ uint8_t ;
struct qm_dqrr {scalar_t__ pmode; int /*<<< orphan*/  fill; scalar_t__ pi; } ;
struct qm_portal {struct qm_dqrr dqrr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  DQRR_PI ; 
 int QM_DQRR_SIZE ; 
 scalar_t__ cyc_diff (int,scalar_t__,scalar_t__) ; 
 scalar_t__ e_QmPortalPCE ; 
 int qm_cl_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ uint8_t qmPortalDqrrPceUpdate(struct qm_portal *portal)
{
    register struct qm_dqrr *dqrr = &portal->dqrr;
    uint8_t diff, old_pi = dqrr->pi;
#ifdef QM_CHECKING
    ASSERT_COND(dqrr->pmode == e_QmPortalPCE);
#endif /* QM_CHECKING */
    dqrr->pi = (uint8_t)(qm_cl_in(DQRR_PI) & (QM_DQRR_SIZE - 1));
    diff = cyc_diff(QM_DQRR_SIZE, old_pi, dqrr->pi);
    dqrr->fill += diff;
    return diff;
}