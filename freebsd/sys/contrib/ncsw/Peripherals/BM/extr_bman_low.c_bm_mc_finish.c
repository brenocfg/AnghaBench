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
struct bm_mc {scalar_t__ state; } ;
struct bm_portal {struct bm_mc mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UNUSED (struct bm_mc*) ; 
 int /*<<< orphan*/  WARNING ; 
 scalar_t__ mc_idle ; 

void bm_mc_finish(struct bm_portal *portal)
{
    register struct bm_mc *mc = &portal->mc;
    ASSERT_COND(mc->state == mc_idle);
#ifdef BM_CHECKING
    if (mc->state != mc_idle)
        REPORT_ERROR(WARNING, E_INVALID_STATE, ("Losing incomplete MC command"));
#else
    UNUSED(mc);
#endif /* BM_CHECKING */
}