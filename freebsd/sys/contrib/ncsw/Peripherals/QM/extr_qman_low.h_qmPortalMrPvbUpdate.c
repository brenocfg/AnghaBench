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
struct qm_mr {int pi; scalar_t__ pmode; int vbit; int /*<<< orphan*/  fill; int /*<<< orphan*/  ring; } ;
struct qm_portal {struct qm_mr mr; } ;
struct qm_mr_entry {int verb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int QM_MR_SIZE ; 
 int QM_MR_VERB_VBIT ; 
 int /*<<< orphan*/  dcbit_ro (struct qm_mr_entry*) ; 
 scalar_t__ e_QmPortalPVB ; 
 struct qm_mr_entry* ptr_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_cl (int) ; 

__attribute__((used)) static __inline__ void qmPortalMrPvbUpdate(struct qm_portal *portal)
{
    register struct qm_mr *mr = &portal->mr;
    struct qm_mr_entry *res = ptr_ADD(mr->ring, qm_cl(mr->pi));
#ifdef QM_CHECKING
    ASSERT_COND(mr->pmode == e_QmPortalPVB);
#endif /* QM_CHECKING */
    dcbit_ro(ptr_ADD(mr->ring, qm_cl(mr->pi)));
    if ((res->verb & QM_MR_VERB_VBIT) == mr->vbit) {
        mr->pi = (uint8_t)((mr->pi + 1) & (QM_MR_SIZE - 1));
        if (!mr->pi)
            mr->vbit ^= QM_MR_VERB_VBIT;
        mr->fill++;
    }
}