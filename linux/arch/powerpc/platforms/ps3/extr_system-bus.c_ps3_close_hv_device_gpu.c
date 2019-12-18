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
struct ps3_system_bus_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; scalar_t__ gpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int lv1_gpu_close () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ usage_hack ; 

__attribute__((used)) static int ps3_close_hv_device_gpu(struct ps3_system_bus_device *dev)
{
	int result;

	mutex_lock(&usage_hack.mutex);

	usage_hack.gpu--;
	if (usage_hack.gpu) {
		result = 0;
		goto done;
	}

	result = lv1_gpu_close();
	BUG_ON(result);

done:
	mutex_unlock(&usage_hack.mutex);
	return result;
}