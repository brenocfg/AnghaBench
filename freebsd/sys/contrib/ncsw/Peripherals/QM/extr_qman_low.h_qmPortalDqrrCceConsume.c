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
struct qm_dqrr {scalar_t__ cmode; int ci; } ;
struct qm_portal {struct qm_dqrr dqrr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  DQRR_CI ; 
 int QM_DQRR_SIZE ; 
 scalar_t__ e_QmPortalDqrrCCE ; 
 int /*<<< orphan*/  qm_cl_out (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline__ void qmPortalDqrrCceConsume(struct qm_portal *portal, uint8_t num)
{
    register struct qm_dqrr *dqrr = &portal->dqrr;
#ifdef QM_CHECKING
    ASSERT_COND(dqrr->cmode == e_QmPortalDqrrCCE);
#endif /* QM_CHECKING */
    dqrr->ci = (uint8_t)((dqrr->ci + num) & (QM_DQRR_SIZE - 1));
    qm_cl_out(DQRR_CI, dqrr->ci);
}