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

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MAKEDEV_ETERNAL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  ctty ; 
 int /*<<< orphan*/  ctty_cdevsw ; 
 int /*<<< orphan*/  ctty_clone ; 
 int /*<<< orphan*/  dev_clone ; 
 int /*<<< orphan*/  make_dev_credf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void
ctty_drvinit(void *unused)
{

	EVENTHANDLER_REGISTER(dev_clone, ctty_clone, 0, 1000);
	ctty = make_dev_credf(MAKEDEV_ETERNAL, &ctty_cdevsw, 0, NULL, UID_ROOT,
	    GID_WHEEL, 0666, "ctty");
}