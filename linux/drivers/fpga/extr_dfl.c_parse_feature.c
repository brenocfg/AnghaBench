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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct dfl_fpga_enum_dfl {scalar_t__ ioaddr; } ;
struct build_feature_devs_info {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 scalar_t__ DFH ; 
 int /*<<< orphan*/  DFH_TYPE ; 
#define  DFH_TYPE_AFU 130 
#define  DFH_TYPE_FIU 129 
#define  DFH_TYPE_PRIVATE 128 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int parse_feature_afu (struct build_feature_devs_info*,struct dfl_fpga_enum_dfl*,scalar_t__) ; 
 int parse_feature_fiu (struct build_feature_devs_info*,struct dfl_fpga_enum_dfl*,scalar_t__) ; 
 int parse_feature_private (struct build_feature_devs_info*,struct dfl_fpga_enum_dfl*,scalar_t__) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 

__attribute__((used)) static int parse_feature(struct build_feature_devs_info *binfo,
			 struct dfl_fpga_enum_dfl *dfl, resource_size_t ofst)
{
	u64 v;
	u32 type;

	v = readq(dfl->ioaddr + ofst + DFH);
	type = FIELD_GET(DFH_TYPE, v);

	switch (type) {
	case DFH_TYPE_AFU:
		return parse_feature_afu(binfo, dfl, ofst);
	case DFH_TYPE_PRIVATE:
		return parse_feature_private(binfo, dfl, ofst);
	case DFH_TYPE_FIU:
		return parse_feature_fiu(binfo, dfl, ofst);
	default:
		dev_info(binfo->dev,
			 "Feature Type %x is not supported.\n", type);
	}

	return 0;
}