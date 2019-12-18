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
struct dfl_fpga_enum_dfl {int dummy; } ;
struct build_feature_devs_info {scalar_t__ ioaddr; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  FEATURE_ID_AFU ; 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_CAP_MMIO_SIZE ; 
 scalar_t__ PORT_HDR_CAP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int create_feature_instance (struct build_feature_devs_info*,struct dfl_fpga_enum_dfl*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 

__attribute__((used)) static int parse_feature_port_afu(struct build_feature_devs_info *binfo,
				  struct dfl_fpga_enum_dfl *dfl,
				  resource_size_t ofst)
{
	u64 v = readq(binfo->ioaddr + PORT_HDR_CAP);
	u32 size = FIELD_GET(PORT_CAP_MMIO_SIZE, v) << 10;

	WARN_ON(!size);

	return create_feature_instance(binfo, dfl, ofst, size, FEATURE_ID_AFU);
}