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
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MAKEDEV_ETERNAL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  fildesc_cdevsw ; 
 int /*<<< orphan*/  make_dev_alias (struct cdev*,char*) ; 
 struct cdev* make_dev_credf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void
fildesc_drvinit(void *unused)
{
	struct cdev *dev;

	dev = make_dev_credf(MAKEDEV_ETERNAL, &fildesc_cdevsw, 0, NULL,
	    UID_ROOT, GID_WHEEL, 0666, "fd/0");
	make_dev_alias(dev, "stdin");
	dev = make_dev_credf(MAKEDEV_ETERNAL, &fildesc_cdevsw, 1, NULL,
	    UID_ROOT, GID_WHEEL, 0666, "fd/1");
	make_dev_alias(dev, "stdout");
	dev = make_dev_credf(MAKEDEV_ETERNAL, &fildesc_cdevsw, 2, NULL,
	    UID_ROOT, GID_WHEEL, 0666, "fd/2");
	make_dev_alias(dev, "stderr");
}