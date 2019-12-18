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
typedef  scalar_t__ u32 ;
struct dfl_fpga_enum_dfl {scalar_t__ ioaddr; } ;
struct build_feature_devs_info {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 scalar_t__ DFH ; 
 int /*<<< orphan*/  DFH_ID ; 
 scalar_t__ FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NEXT_AFU ; 
 int /*<<< orphan*/  NEXT_AFU_NEXT_DFH_OFST ; 
 int build_info_create_dev (struct build_feature_devs_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 int create_feature_instance (struct build_feature_devs_info*,struct dfl_fpga_enum_dfl*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dfh_id_to_type (scalar_t__) ; 
 int parse_feature_afu (struct build_feature_devs_info*,struct dfl_fpga_enum_dfl*,scalar_t__) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 

__attribute__((used)) static int parse_feature_fiu(struct build_feature_devs_info *binfo,
			     struct dfl_fpga_enum_dfl *dfl,
			     resource_size_t ofst)
{
	u32 id, offset;
	u64 v;
	int ret = 0;

	v = readq(dfl->ioaddr + ofst + DFH);
	id = FIELD_GET(DFH_ID, v);

	/* create platform device for dfl feature dev */
	ret = build_info_create_dev(binfo, dfh_id_to_type(id),
				    dfl->ioaddr + ofst);
	if (ret)
		return ret;

	ret = create_feature_instance(binfo, dfl, ofst, 0, 0);
	if (ret)
		return ret;
	/*
	 * find and parse FIU's child AFU via its NEXT_AFU register.
	 * please note that only Port has valid NEXT_AFU pointer per spec.
	 */
	v = readq(dfl->ioaddr + ofst + NEXT_AFU);

	offset = FIELD_GET(NEXT_AFU_NEXT_DFH_OFST, v);
	if (offset)
		return parse_feature_afu(binfo, dfl, ofst + offset);

	dev_dbg(binfo->dev, "No AFUs detected on FIU %d\n", id);

	return ret;
}