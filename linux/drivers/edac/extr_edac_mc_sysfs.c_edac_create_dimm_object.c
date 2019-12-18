#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mem_ctl_info {int /*<<< orphan*/  dev; scalar_t__ csbased; } ;
struct TYPE_7__ {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * type; } ;
struct dimm_info {TYPE_1__ dev; struct mem_ctl_info* mci; } ;
typedef  int /*<<< orphan*/  location ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_EDAC_DEBUG ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct dimm_info*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  dimm_attr_type ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  edac_dimm_info_location (struct dimm_info*,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

__attribute__((used)) static int edac_create_dimm_object(struct mem_ctl_info *mci,
				   struct dimm_info *dimm,
				   int index)
{
	int err;
	dimm->mci = mci;

	dimm->dev.type = &dimm_attr_type;
	device_initialize(&dimm->dev);

	dimm->dev.parent = &mci->dev;
	if (mci->csbased)
		dev_set_name(&dimm->dev, "rank%d", index);
	else
		dev_set_name(&dimm->dev, "dimm%d", index);
	dev_set_drvdata(&dimm->dev, dimm);
	pm_runtime_forbid(&mci->dev);

	err = device_add(&dimm->dev);
	if (err) {
		edac_dbg(1, "failure: create device %s\n", dev_name(&dimm->dev));
		put_device(&dimm->dev);
		return err;
	}

	if (IS_ENABLED(CONFIG_EDAC_DEBUG)) {
		char location[80];

		edac_dimm_info_location(dimm, location, sizeof(location));
		edac_dbg(0, "device %s created at location %s\n",
			dev_name(&dimm->dev), location);
	}

	return 0;
}