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
struct qm_mr {scalar_t__ cmode; } ;
struct qm_portal {struct qm_mr mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  MR_CI ; 
 scalar_t__ e_QmPortalMrCCE ; 
 int /*<<< orphan*/  qm_cl_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_cl_touch_rw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void qmPortalMrCcePrefetch(struct qm_portal *portal)
{
#ifdef QM_CHECKING
    register struct qm_mr *mr = &portal->mr;
    ASSERT_COND(mr->cmode == e_QmPortalMrCCE);
#endif /* QM_CHECKING */
    qm_cl_invalidate(MR_CI);
    qm_cl_touch_rw(MR_CI);
}