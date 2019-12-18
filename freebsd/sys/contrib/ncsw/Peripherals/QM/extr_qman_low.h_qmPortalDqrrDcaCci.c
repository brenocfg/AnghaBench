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
typedef  int /*<<< orphan*/  uint8_t ;
struct qm_dqrr {scalar_t__ cmode; } ;
struct qm_portal {struct qm_dqrr dqrr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  DQRR_CI_CINH ; 
 int QM_DQRR_SIZE ; 
 scalar_t__ e_QmPortalDqrrDCA ; 
 int qm_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ uint8_t qmPortalDqrrDcaCci(struct qm_portal *portal)
{
#ifdef QM_CHECKING
    register struct qm_dqrr *dqrr = &portal->dqrr;
    ASSERT_COND(dqrr->cmode == e_QmPortalDqrrDCA);
#endif /* QM_CHECKING */
    return (uint8_t)(qm_in(DQRR_CI_CINH) & (QM_DQRR_SIZE - 1));
}