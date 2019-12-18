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
struct qm_mr {scalar_t__ cmode; int /*<<< orphan*/  ci; int /*<<< orphan*/  cursor; } ;
struct qm_portal {struct qm_mr mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  MR_CI ; 
 int /*<<< orphan*/  MR_PTR2IDX (int /*<<< orphan*/ ) ; 
 scalar_t__ e_QmPortalMrCCE ; 
 int /*<<< orphan*/  qm_cl_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void qmPortalMrCceConsumeToCurrent(struct qm_portal *portal)
{
    register struct qm_mr *mr = &portal->mr;
#ifdef QM_CHECKING
    ASSERT_COND(mr->cmode == e_QmPortalMrCCE);
#endif /* QM_CHECKING */
    mr->ci = MR_PTR2IDX(mr->cursor);
    qm_cl_out(MR_CI, mr->ci);
}