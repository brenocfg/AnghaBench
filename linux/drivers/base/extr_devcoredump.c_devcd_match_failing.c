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
struct devcd_entry {void const* failing_dev; } ;

/* Variables and functions */
 struct devcd_entry* dev_to_devcd (struct device*) ; 

__attribute__((used)) static int devcd_match_failing(struct device *dev, const void *failing)
{
	struct devcd_entry *devcd = dev_to_devcd(dev);

	return devcd->failing_dev == failing;
}