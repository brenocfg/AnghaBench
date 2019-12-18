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

/* Variables and functions */
 int sdei_device_thaw (struct device*) ; 
 int sdei_platform_reset () ; 

__attribute__((used)) static int sdei_device_restore(struct device *dev)
{
	int err;

	err = sdei_platform_reset();
	if (err)
		return err;

	return sdei_device_thaw(dev);
}