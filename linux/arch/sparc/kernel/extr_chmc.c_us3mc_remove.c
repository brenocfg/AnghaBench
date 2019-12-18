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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MC_TYPE_JBUS ; 
 scalar_t__ MC_TYPE_SAFARI ; 
 int /*<<< orphan*/  chmc_destroy (struct platform_device*,void*) ; 
 void* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbusmc_destroy (struct platform_device*,void*) ; 
 scalar_t__ mc_type ; 

__attribute__((used)) static int us3mc_remove(struct platform_device *op)
{
	void *p = dev_get_drvdata(&op->dev);

	if (p) {
		if (mc_type == MC_TYPE_SAFARI)
			chmc_destroy(op, p);
		else if (mc_type == MC_TYPE_JBUS)
			jbusmc_destroy(op, p);
	}
	return 0;
}