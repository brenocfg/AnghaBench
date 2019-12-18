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
struct lm_driver {int /*<<< orphan*/  (* remove ) (struct lm_device*) ;} ;
struct lm_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct lm_device*) ; 
 struct lm_device* to_lm_device (struct device*) ; 
 struct lm_driver* to_lm_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm_bus_remove(struct device *dev)
{
	struct lm_device *lmdev = to_lm_device(dev);
	struct lm_driver *lmdrv = to_lm_driver(dev->driver);

	if (lmdrv->remove)
		lmdrv->remove(lmdev);
	return 0;
}