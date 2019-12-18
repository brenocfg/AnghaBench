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
struct qm_mc {scalar_t__ state; struct qm_mc_command* cr; } ;
struct qm_portal {struct qm_mc mc; } ;
struct qm_mc_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  dcbz_64 (struct qm_mc_command*) ; 
 scalar_t__ mc_idle ; 
 scalar_t__ mc_user ; 

__attribute__((used)) static __inline__ struct qm_mc_command *qm_mc_start(struct qm_portal *portal)
{
    register struct qm_mc *mc = &portal->mc;
#ifdef QM_CHECKING
    ASSERT_COND(mc->state == mc_idle);
    mc->state = mc_user;
#endif /* QM_CHECKING */
    dcbz_64(mc->cr);
    return mc->cr;
}