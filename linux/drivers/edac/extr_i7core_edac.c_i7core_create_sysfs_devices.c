#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  bus; } ;
struct mem_ctl_info {TYPE_1__ dev; struct i7core_pvt* pvt_info; } ;
struct i7core_pvt {TYPE_2__* addrmatch_dev; TYPE_2__* chancounts_dev; int /*<<< orphan*/  is_registered; } ;
struct TYPE_10__ {TYPE_1__* parent; int /*<<< orphan*/  bus; int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  addrmatch_type ; 
 int /*<<< orphan*/  all_channel_counts_type ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct mem_ctl_info*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_del (TYPE_2__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 

__attribute__((used)) static int i7core_create_sysfs_devices(struct mem_ctl_info *mci)
{
	struct i7core_pvt *pvt = mci->pvt_info;
	int rc;

	pvt->addrmatch_dev = kzalloc(sizeof(*pvt->addrmatch_dev), GFP_KERNEL);
	if (!pvt->addrmatch_dev)
		return -ENOMEM;

	pvt->addrmatch_dev->type = &addrmatch_type;
	pvt->addrmatch_dev->bus = mci->dev.bus;
	device_initialize(pvt->addrmatch_dev);
	pvt->addrmatch_dev->parent = &mci->dev;
	dev_set_name(pvt->addrmatch_dev, "inject_addrmatch");
	dev_set_drvdata(pvt->addrmatch_dev, mci);

	edac_dbg(1, "creating %s\n", dev_name(pvt->addrmatch_dev));

	rc = device_add(pvt->addrmatch_dev);
	if (rc < 0)
		goto err_put_addrmatch;

	if (!pvt->is_registered) {
		pvt->chancounts_dev = kzalloc(sizeof(*pvt->chancounts_dev),
					      GFP_KERNEL);
		if (!pvt->chancounts_dev) {
			rc = -ENOMEM;
			goto err_del_addrmatch;
		}

		pvt->chancounts_dev->type = &all_channel_counts_type;
		pvt->chancounts_dev->bus = mci->dev.bus;
		device_initialize(pvt->chancounts_dev);
		pvt->chancounts_dev->parent = &mci->dev;
		dev_set_name(pvt->chancounts_dev, "all_channel_counts");
		dev_set_drvdata(pvt->chancounts_dev, mci);

		edac_dbg(1, "creating %s\n", dev_name(pvt->chancounts_dev));

		rc = device_add(pvt->chancounts_dev);
		if (rc < 0)
			goto err_put_chancounts;
	}
	return 0;

err_put_chancounts:
	put_device(pvt->chancounts_dev);
err_del_addrmatch:
	device_del(pvt->addrmatch_dev);
err_put_addrmatch:
	put_device(pvt->addrmatch_dev);

	return rc;
}