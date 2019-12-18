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
struct qm_dqrr {scalar_t__ cmode; struct qm_dqrr_entry* ring; } ;
struct qm_portal {struct qm_dqrr dqrr; } ;
struct qm_dqrr_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  DQRR_DCAP ; 
 int DQRR_PTR2IDX (struct qm_dqrr_entry*) ; 
 int QM_DQRR_SIZE ; 
 scalar_t__ e_QmPortalDqrrDCA ; 
 int /*<<< orphan*/  qm_out (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline__ void qmPortalDqrrDcaConsume1ptr(struct qm_portal      *portal,
                                                  struct qm_dqrr_entry  *dq,
                                                  bool                  park)
{
    uint8_t idx = DQRR_PTR2IDX(dq);
#ifdef QM_CHECKING
    register struct qm_dqrr *dqrr = &portal->dqrr;

    ASSERT_COND(dqrr->cmode == e_QmPortalDqrrDCA);
    ASSERT_COND((dqrr->ring + idx) == dq);
    ASSERT_COND(idx < QM_DQRR_SIZE);
#endif /* QM_CHECKING */
    qm_out(DQRR_DCAP, (0 << 8) |        /* DQRR_DCAP::S */
        ((uint32_t)(park ? 1 : 0) << 6) |        /* DQRR_DCAP::PK */
        idx);                /* DQRR_DCAP::DCAP_CI */
}