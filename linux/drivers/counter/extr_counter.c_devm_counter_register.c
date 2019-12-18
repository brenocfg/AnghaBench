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
struct device {int dummy; } ;
struct counter_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int counter_register (struct counter_device* const) ; 
 int /*<<< orphan*/  devm_counter_unreg ; 
 int /*<<< orphan*/  devres_add (struct device*,struct counter_device**) ; 
 struct counter_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct counter_device**) ; 

int devm_counter_register(struct device *dev,
			  struct counter_device *const counter)
{
	struct counter_device **ptr;
	int ret;

	ptr = devres_alloc(devm_counter_unreg, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	ret = counter_register(counter);
	if (!ret) {
		*ptr = counter;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return ret;
}