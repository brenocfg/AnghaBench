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
struct locomo_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct locomo_dev* LOCOMO_DEV (struct device*) ; 
 int /*<<< orphan*/  kfree (struct locomo_dev*) ; 

__attribute__((used)) static void locomo_dev_release(struct device *_dev)
{
	struct locomo_dev *dev = LOCOMO_DEV(_dev);

	kfree(dev);
}