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
struct qm_mc {scalar_t__ state; } ;
struct qm_portal {struct qm_mc mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  QM_BIND_MC ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  __qm_portal_unbind (struct qm_portal*,int /*<<< orphan*/ ) ; 
 scalar_t__ mc_idle ; 

__attribute__((used)) static __inline__ void qm_mc_finish(struct qm_portal *portal)
{
#ifdef QM_CHECKING
    register struct qm_mc *mc = &portal->mc;
    ASSERT_COND(mc->state == mc_idle);
    if (mc->state != mc_idle)
        REPORT_ERROR(WARNING, E_INVALID_STATE, ("Losing incomplete MC command"));
#endif /* QM_CHECKING */
    __qm_portal_unbind(portal, QM_BIND_MC);
}