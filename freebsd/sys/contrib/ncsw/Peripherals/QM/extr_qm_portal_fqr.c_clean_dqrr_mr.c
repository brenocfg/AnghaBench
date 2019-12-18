#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  p_LowQmPortal; } ;
typedef  TYPE_1__ t_QmPortal ;
struct qm_mr_entry {int dummy; } ;
struct qm_dqrr_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XX_UDelay (int) ; 
 int /*<<< orphan*/  qmPortalDqrrCciConsume (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qmPortalDqrrPvbPrefetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmPortalDqrrPvbUpdate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmPortalMrCciConsume (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qmPortalMrPvbUpdate (int /*<<< orphan*/ ) ; 
 struct qm_dqrr_entry* qm_dqrr_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_dqrr_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_dqrr_sdqcr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_dqrr_vdqcr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qm_mr_entry* qm_mr_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_mr_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clean_dqrr_mr(t_QmPortal *p_QmPortal)
{
    struct qm_dqrr_entry    *p_Dq;
    struct qm_mr_entry      *p_Msg;
    int                     idle = 0;

    qm_dqrr_sdqcr_set(p_QmPortal->p_LowQmPortal, 0);
    qm_dqrr_vdqcr_set(p_QmPortal->p_LowQmPortal, 0);
drain_loop:
    qmPortalDqrrPvbPrefetch(p_QmPortal->p_LowQmPortal);
    qmPortalDqrrPvbUpdate(p_QmPortal->p_LowQmPortal);
    qmPortalMrPvbUpdate(p_QmPortal->p_LowQmPortal);
    p_Dq = qm_dqrr_current(p_QmPortal->p_LowQmPortal);
    p_Msg = qm_mr_current(p_QmPortal->p_LowQmPortal);
    if (p_Dq) {
        qm_dqrr_next(p_QmPortal->p_LowQmPortal);
        qmPortalDqrrCciConsume(p_QmPortal->p_LowQmPortal, 1);
    }
    if (p_Msg) {
    qm_mr_next(p_QmPortal->p_LowQmPortal);
        qmPortalMrCciConsume(p_QmPortal->p_LowQmPortal, 1);
    }
    if (!p_Dq && !p_Msg) {
    if (++idle < 5) {
    XX_UDelay(1000);
    goto drain_loop;
    }
    } else {
    idle = 0;
    goto drain_loop;
    }
}