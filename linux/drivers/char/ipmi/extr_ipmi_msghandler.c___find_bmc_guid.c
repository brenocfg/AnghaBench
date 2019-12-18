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
struct device {int /*<<< orphan*/ * type; } ;
struct bmc_device {int /*<<< orphan*/  usecount; int /*<<< orphan*/  guid; scalar_t__ dyn_guid_set; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  bmc_device_type ; 
 scalar_t__ guid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 struct bmc_device* to_bmc_device (struct device*) ; 

__attribute__((used)) static int __find_bmc_guid(struct device *dev, const void *data)
{
	const guid_t *guid = data;
	struct bmc_device *bmc;
	int rv;

	if (dev->type != &bmc_device_type)
		return 0;

	bmc = to_bmc_device(dev);
	rv = bmc->dyn_guid_set && guid_equal(&bmc->guid, guid);
	if (rv)
		rv = kref_get_unless_zero(&bmc->usecount);
	return rv;
}