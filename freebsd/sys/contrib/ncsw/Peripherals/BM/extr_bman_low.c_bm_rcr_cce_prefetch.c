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
struct bm_rcr {scalar_t__ cmode; } ;
struct bm_portal {int /*<<< orphan*/  rcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  RCR_CI ; 
 int /*<<< orphan*/  bm_cl_touch_ro (int /*<<< orphan*/ ) ; 
 scalar_t__ e_BmPortalRcrCCE ; 

void bm_rcr_cce_prefetch(struct bm_portal *portal)
{
    ASSERT_COND(((struct bm_rcr *)&portal->rcr)->cmode == e_BmPortalRcrCCE);
    bm_cl_touch_ro(RCR_CI);
}