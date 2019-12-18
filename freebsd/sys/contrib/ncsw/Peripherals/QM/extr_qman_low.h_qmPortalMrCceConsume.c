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
struct qm_mr {scalar_t__ cmode; int ci; } ;
struct qm_portal {struct qm_mr mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  MR_CI ; 
 int QM_MR_SIZE ; 
 scalar_t__ e_QmPortalMrCCE ; 
 int /*<<< orphan*/  qm_cl_out (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline__ void qmPortalMrCceConsume(struct qm_portal *portal, uint8_t num)
{
    register struct qm_mr *mr = &portal->mr;
#ifdef QM_CHECKING
    ASSERT_COND(mr->cmode == e_QmPortalMrCCE);
#endif /* QM_CHECKING */
    mr->ci = (uint8_t)((mr->ci + num) & (QM_MR_SIZE - 1));
    qm_cl_out(MR_CI, mr->ci);
}