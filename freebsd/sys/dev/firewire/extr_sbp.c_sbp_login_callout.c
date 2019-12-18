#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sbp_dev {TYPE_1__* target; } ;
struct TYPE_2__ {int /*<<< orphan*/  sbp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ORB_FUN_LGI ; 
 int /*<<< orphan*/  SBP_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbp_mgm_orb (struct sbp_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sbp_login_callout(void *arg)
{
	struct sbp_dev *sdev = (struct sbp_dev *)arg;
	SBP_LOCK_ASSERT(sdev->target->sbp);
	sbp_mgm_orb(sdev, ORB_FUN_LGI, NULL);
}