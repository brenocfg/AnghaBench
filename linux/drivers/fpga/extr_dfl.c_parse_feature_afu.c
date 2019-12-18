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
struct dfl_fpga_enum_dfl {int dummy; } ;
struct build_feature_devs_info {TYPE_1__* feature_dev; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PORT_ID 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int feature_dev_id_type (TYPE_1__*) ; 
 int parse_feature_port_afu (struct build_feature_devs_info*,struct dfl_fpga_enum_dfl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_feature_afu(struct build_feature_devs_info *binfo,
			     struct dfl_fpga_enum_dfl *dfl,
			     resource_size_t ofst)
{
	if (!binfo->feature_dev) {
		dev_err(binfo->dev, "this AFU does not belong to any FIU.\n");
		return -EINVAL;
	}

	switch (feature_dev_id_type(binfo->feature_dev)) {
	case PORT_ID:
		return parse_feature_port_afu(binfo, dfl, ofst);
	default:
		dev_info(binfo->dev, "AFU belonging to FIU %s is not supported yet.\n",
			 binfo->feature_dev->name);
	}

	return 0;
}