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
struct qm_eqcr {int busy; struct qm_eqcr_entry* cursor; int /*<<< orphan*/  available; } ;
struct qm_portal {struct qm_eqcr eqcr; } ;
struct qm_eqcr_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  dcbz_64 (struct qm_eqcr_entry*) ; 

__attribute__((used)) static __inline__ struct qm_eqcr_entry *qm_eqcr_start(struct qm_portal *portal)
{
    register struct qm_eqcr *eqcr = &portal->eqcr;
#ifdef QM_CHECKING
    ASSERT_COND(!eqcr->busy);
#endif /* QM_CHECKING */
    if (!eqcr->available)
        return NULL;
#ifdef QM_CHECKING
    eqcr->busy = 1;
#endif /* QM_CHECKING */
    dcbz_64(eqcr->cursor);
    return eqcr->cursor;
}