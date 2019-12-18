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
struct qm_mr {scalar_t__ ci; int /*<<< orphan*/  cursor; } ;
struct qm_portal {struct qm_mr mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_STATE ; 
 scalar_t__ MR_PTR2IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QM_BIND_MR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  __qm_portal_unbind (struct qm_portal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void qm_mr_finish(struct qm_portal *portal)
{
    register struct qm_mr *mr = &portal->mr;
    if (mr->ci != MR_PTR2IDX(mr->cursor))
        REPORT_ERROR(WARNING, E_INVALID_STATE, ("Ignoring completed MR entries"));
    __qm_portal_unbind(portal, QM_BIND_MR);
}