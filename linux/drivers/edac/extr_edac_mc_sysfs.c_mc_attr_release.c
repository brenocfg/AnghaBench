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
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct device*) ; 

__attribute__((used)) static void mc_attr_release(struct device *dev)
{
	/*
	 * There's no container structure here, as this is just the mci
	 * parent device, used to create the /sys/devices/mc sysfs node.
	 * So, there are no attributes on it.
	 */
	edac_dbg(1, "device %s released\n", dev_name(dev));
	kfree(dev);
}