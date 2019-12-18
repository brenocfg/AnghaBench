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
 int /*<<< orphan*/  UNUSED (struct bm_mc*) ; 
 scalar_t__ mc_idle ; 
 scalar_t__ mc_user ; 

void bm_mc_abort(struct bm_portal *portal)
{
    register struct bm_mc *mc = &portal->mc;
    ASSERT_COND(mc->state == mc_user);
#ifdef BM_CHECKING
    mc->state = mc_idle;
#else
    UNUSED(mc);
#endif /* BM_CHECKING */
}