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
typedef  int uint8_t ;
struct qm_dqrr {int pi; scalar_t__ pmode; int vbit; int /*<<< orphan*/  fill; int /*<<< orphan*/  ring; } ;
struct qm_portal {struct qm_dqrr dqrr; } ;
struct qm_dqrr_entry {int verb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int QM_DQRR_SIZE ; 
 int QM_DQRR_VERB_VBIT ; 
 scalar_t__ e_QmPortalPVB ; 
 struct qm_dqrr_entry* ptr_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_cl (int) ; 

__attribute__((used)) static __inline__ uint8_t qmPortalDqrrPvbUpdate(struct qm_portal *portal)
{
    register struct qm_dqrr *dqrr = &portal->dqrr;
    struct qm_dqrr_entry *res = ptr_ADD(dqrr->ring, qm_cl(dqrr->pi));
#ifdef QM_CHECKING
    ASSERT_COND(dqrr->pmode == e_QmPortalPVB);
#endif /* QM_CHECKING */
    if ((res->verb & QM_DQRR_VERB_VBIT) == dqrr->vbit) {
        dqrr->pi = (uint8_t)((dqrr->pi + 1) & (QM_DQRR_SIZE - 1));
        if (!dqrr->pi)
            dqrr->vbit ^= QM_DQRR_VERB_VBIT;
        dqrr->fill++;
        return 1;
    }
    return 0;
}