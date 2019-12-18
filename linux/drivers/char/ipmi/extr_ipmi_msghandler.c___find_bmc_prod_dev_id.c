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
struct prod_dev_id {scalar_t__ product_id; scalar_t__ device_id; } ;
struct device {int /*<<< orphan*/ * type; } ;
struct TYPE_2__ {scalar_t__ product_id; scalar_t__ device_id; } ;
struct bmc_device {int /*<<< orphan*/  usecount; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  bmc_device_type ; 
 int kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 struct bmc_device* to_bmc_device (struct device*) ; 

__attribute__((used)) static int __find_bmc_prod_dev_id(struct device *dev, const void *data)
{
	const struct prod_dev_id *cid = data;
	struct bmc_device *bmc;
	int rv;

	if (dev->type != &bmc_device_type)
		return 0;

	bmc = to_bmc_device(dev);
	rv = (bmc->id.product_id == cid->product_id
	      && bmc->id.device_id == cid->device_id);
	if (rv)
		rv = kref_get_unless_zero(&bmc->usecount);
	return rv;
}