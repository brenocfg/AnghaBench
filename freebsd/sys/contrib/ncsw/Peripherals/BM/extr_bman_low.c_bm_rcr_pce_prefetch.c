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
struct bm_rcr {scalar_t__ pmode; } ;
struct bm_portal {int /*<<< orphan*/  rcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  RCR_PI ; 
 int /*<<< orphan*/  bm_cl_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_cl_touch_rw (int /*<<< orphan*/ ) ; 
 scalar_t__ e_BmPortalPCE ; 

void bm_rcr_pce_prefetch(struct bm_portal *portal)
{
    ASSERT_COND(((struct bm_rcr *)&portal->rcr)->pmode == e_BmPortalPCE);
    bm_cl_invalidate(RCR_PI);
    bm_cl_touch_rw(RCR_PI);
}