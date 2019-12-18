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
typedef  int uint32_t ;
struct qm_dqrr {scalar_t__ cmode; } ;
struct qm_portal {struct qm_dqrr dqrr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  DQRR_DCAP ; 
 int QM_DQRR_SIZE ; 
 scalar_t__ e_QmPortalDqrrDCA ; 
 int /*<<< orphan*/  qm_out (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline__ void qm_dqrr_park(struct qm_portal *portal, uint8_t idx)
{
#ifdef QM_CHECKING
    register struct qm_dqrr *dqrr = &portal->dqrr;
    ASSERT_COND(dqrr->cmode != e_QmPortalDqrrDCA);
#endif /* QM_CHECKING */

    qm_out(DQRR_DCAP, (0 << 8) |        /* S */
        (uint32_t)(1 << 6) |            /* PK */
        (idx & (QM_DQRR_SIZE - 1)));    /* DCAP_CI */
}