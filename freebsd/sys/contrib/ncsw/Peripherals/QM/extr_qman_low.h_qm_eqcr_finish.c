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
struct qm_eqcr {scalar_t__ ci; int /*<<< orphan*/  cursor; int /*<<< orphan*/  busy; } ;
struct qm_portal {struct qm_eqcr eqcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  EQCR_CI_CINH ; 
 int /*<<< orphan*/  EQCR_PI_CINH ; 
 scalar_t__ EQCR_PTR2IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  QM_BIND_EQCR ; 
 int QM_EQCR_SIZE ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  __qm_portal_unbind (struct qm_portal*,int /*<<< orphan*/ ) ; 
 int qm_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void qm_eqcr_finish(struct qm_portal *portal)
{
    register struct qm_eqcr *eqcr = &portal->eqcr;
    uint8_t pi = (uint8_t)(qm_in(EQCR_PI_CINH) & (QM_EQCR_SIZE - 1));
    uint8_t ci = (uint8_t)(qm_in(EQCR_CI_CINH) & (QM_EQCR_SIZE - 1));

#ifdef QM_CHECKING
    ASSERT_COND(!eqcr->busy);
#endif /* QM_CHECKING */
    if (pi != EQCR_PTR2IDX(eqcr->cursor))
        REPORT_ERROR(WARNING, E_INVALID_STATE, ("losing uncommitted EQCR entries"));
    if (ci != eqcr->ci)
        REPORT_ERROR(WARNING, E_INVALID_STATE, ("missing existing EQCR completions"));
    if (eqcr->ci != EQCR_PTR2IDX(eqcr->cursor))
        REPORT_ERROR(WARNING, E_INVALID_STATE, ("EQCR destroyed unquiesced"));
    __qm_portal_unbind(portal, QM_BIND_EQCR);
}