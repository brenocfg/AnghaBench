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
struct qm_mc {int rridx; scalar_t__ state; int /*<<< orphan*/  vbit; struct qm_mc_result* rr; } ;
struct qm_portal {struct qm_mc mc; } ;
struct qm_mc_result {int /*<<< orphan*/  verb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  QM_MCC_VERB_VBIT ; 
 int /*<<< orphan*/  dcbit_ro (struct qm_mc_result*) ; 
 scalar_t__ mc_hw ; 
 scalar_t__ mc_idle ; 

__attribute__((used)) static __inline__ struct qm_mc_result *qm_mc_result(struct qm_portal *portal)
{
    register struct qm_mc *mc = &portal->mc;
    struct qm_mc_result *rr = mc->rr + mc->rridx;
#ifdef QM_CHECKING
    ASSERT_COND(mc->state == mc_hw);
#endif /* QM_CHECKING */
    /* The inactive response register's verb byte always returns zero until
     * its command is submitted and completed. This includes the valid-bit,
     * in case you were wondering... */
    if (!rr->verb) {
        dcbit_ro(rr);
        return NULL;
    }
    mc->rridx ^= 1;
    mc->vbit ^= QM_MCC_VERB_VBIT;
#ifdef QM_CHECKING
    mc->state = mc_idle;
#endif /* QM_CHECKING */
    return rr;
}