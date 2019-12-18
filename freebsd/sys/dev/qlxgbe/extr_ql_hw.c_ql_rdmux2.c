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
struct TYPE_3__ {int select_addr_1; int select_addr_2; int select_value_1; int select_value_2; int select_value_count; int select_value_mask; int read_addr; scalar_t__ select_value_stride; } ;
typedef  TYPE_1__ ql_minidump_entry_mux2_t ;

/* Variables and functions */
 int ql_rdwr_indreg32 (int /*<<< orphan*/ *,int,int*,int) ; 

__attribute__((used)) static uint32_t
ql_rdmux2(qla_host_t *ha,
	ql_minidump_entry_mux2_t *muxEntry,
	uint32_t *data_buff)
{
	int ret;
        int loop_cnt;

        uint32_t select_addr_1, select_addr_2;
        uint32_t select_value_1, select_value_2;
        uint32_t select_value_count, select_value_mask;
        uint32_t read_addr, read_value;

        select_addr_1 = muxEntry->select_addr_1;
        select_addr_2 = muxEntry->select_addr_2;
        select_value_1 = muxEntry->select_value_1;
        select_value_2 = muxEntry->select_value_2;
        select_value_count = muxEntry->select_value_count;
        select_value_mask  = muxEntry->select_value_mask;

        read_addr = muxEntry->read_addr;

        for (loop_cnt = 0; loop_cnt < muxEntry->select_value_count;
		loop_cnt++) {

                uint32_t temp_sel_val;

		ret = ql_rdwr_indreg32(ha, select_addr_1, &select_value_1, 0);
		if (ret)
			return (0);

                temp_sel_val = select_value_1 & select_value_mask;

		ret = ql_rdwr_indreg32(ha, select_addr_2, &temp_sel_val, 0);
		if (ret)
			return (0);

		ret = ql_rdwr_indreg32(ha, read_addr, &read_value, 1);
		if (ret)
			return (0);

                *data_buff++ = temp_sel_val;
                *data_buff++ = read_value;

		ret = ql_rdwr_indreg32(ha, select_addr_1, &select_value_2, 0);
		if (ret)
			return (0);

                temp_sel_val = select_value_2 & select_value_mask;

		ret = ql_rdwr_indreg32(ha, select_addr_2, &temp_sel_val, 0);
		if (ret)
			return (0);

		ret = ql_rdwr_indreg32(ha, read_addr, &read_value, 1);
		if (ret)
			return (0);

                *data_buff++ = temp_sel_val;
                *data_buff++ = read_value;

                select_value_1 += muxEntry->select_value_stride;
                select_value_2 += muxEntry->select_value_stride;
        }

        return (loop_cnt * (4 * sizeof(uint32_t)));
}