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
struct qm_mr {scalar_t__ pmode; int /*<<< orphan*/  fill; scalar_t__ pi; } ;
struct qm_portal {struct qm_mr mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  MR_PI ; 
 int QM_MR_SIZE ; 
 scalar_t__ cyc_diff (int,scalar_t__,scalar_t__) ; 
 scalar_t__ e_QmPortalPCE ; 
 int qm_cl_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ uint8_t qmPortalMrPceUpdate(struct qm_portal *portal)
{
    register struct qm_mr *mr = &portal->mr;
    uint8_t diff, old_pi = mr->pi;
#ifdef QM_CHECKING
    ASSERT_COND(mr->pmode == e_QmPortalPCE);
#endif /* QM_CHECKING */
    mr->pi = (uint8_t)(qm_cl_in(MR_PI) & (QM_MR_SIZE - 1));
    diff = cyc_diff(QM_MR_SIZE, old_pi, mr->pi);
    mr->fill += diff;
    return diff;
}