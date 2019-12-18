#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;
struct TYPE_3__ {int op_count; int read_addr; int control_addr; int tag_reg_addr; int init_tag_value; int read_addr_cnt; scalar_t__ tag_value_stride; scalar_t__ read_addr_stride; int /*<<< orphan*/  write_value; } ;
typedef  TYPE_1__ ql_minidump_entry_cache_t ;

/* Variables and functions */
 int ql_rdwr_indreg32 (int /*<<< orphan*/ *,int,int*,int) ; 

__attribute__((used)) static uint32_t 
ql_L1Cache(qla_host_t *ha,
	ql_minidump_entry_cache_t *cacheEntry,
	uint32_t *data_buff)
{
	int ret;
	int i, k;
	int loop_cnt;

	uint32_t read_value;
	uint32_t addr, read_addr, cntrl_addr, tag_reg_addr;
	uint32_t tag_value, read_cnt;
	uint32_t cntl_value_w;

	loop_cnt = cacheEntry->op_count;

	read_addr = cacheEntry->read_addr;
	cntrl_addr = cacheEntry->control_addr;
	cntl_value_w = (uint32_t) cacheEntry->write_value;

	tag_reg_addr = cacheEntry->tag_reg_addr;

	tag_value = cacheEntry->init_tag_value;
	read_cnt = cacheEntry->read_addr_cnt;

	for (i = 0; i < loop_cnt; i++) {

		ret = ql_rdwr_indreg32(ha, tag_reg_addr, &tag_value, 0);
		if (ret)
			return (0);

		ret = ql_rdwr_indreg32(ha, cntrl_addr, &cntl_value_w, 0);
		if (ret)
			return (0);

		addr = read_addr;
		for (k = 0; k < read_cnt; k++) {

			ret = ql_rdwr_indreg32(ha, addr, &read_value, 1);
			if (ret)
				return (0);

			*data_buff++ = read_value;
			addr += cacheEntry->read_addr_stride;
		}

		tag_value += cacheEntry->tag_value_stride;
	}

	return (read_cnt * loop_cnt * sizeof(uint32_t));
}