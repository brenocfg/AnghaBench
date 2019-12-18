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
struct qm_eqcr {scalar_t__ cmode; int /*<<< orphan*/  available; scalar_t__ ci; } ;
struct qm_portal {struct qm_eqcr eqcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  EQCR_CI_CINH ; 
 int QM_EQCR_SIZE ; 
 scalar_t__ cyc_diff (int,scalar_t__,scalar_t__) ; 
 scalar_t__ e_QmPortalEqcrCCI ; 
 int qm_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ uint8_t qmPortalEqcrCciUpdate(struct qm_portal *portal)
{
    register struct qm_eqcr *eqcr = &portal->eqcr;
    uint8_t diff, old_ci = eqcr->ci;
#ifdef QM_CHECKING
    ASSERT_COND(eqcr->cmode == e_QmPortalEqcrCCI);
#endif /* QM_CHECKING */
    eqcr->ci = (uint8_t)(qm_in(EQCR_CI_CINH) & (QM_EQCR_SIZE - 1));
    diff = cyc_diff(QM_EQCR_SIZE, old_ci, eqcr->ci);
    eqcr->available += diff;
    return diff;
}