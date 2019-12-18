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
struct qm_eqcr_entry {int dummy; } ;
struct qm_eqcr {int /*<<< orphan*/  vbit; struct qm_eqcr_entry* cursor; } ;

/* Variables and functions */
 struct qm_eqcr_entry* EQCR_CARRYCLEAR (struct qm_eqcr_entry*) ; 
 int /*<<< orphan*/  QM_EQCR_VERB_VBIT ; 

__attribute__((used)) static __inline__ void EQCR_INC(struct qm_eqcr *eqcr)
{
    /* NB: this is odd-looking, but experiments show that it generates fast
     * code with essentially no branching overheads. We increment to the
     * next EQCR pointer and handle overflow and 'vbit'. */
    struct qm_eqcr_entry *partial = eqcr->cursor + 1;
    eqcr->cursor = EQCR_CARRYCLEAR(partial);
    if (partial != eqcr->cursor)
        eqcr->vbit ^= QM_EQCR_VERB_VBIT;
}