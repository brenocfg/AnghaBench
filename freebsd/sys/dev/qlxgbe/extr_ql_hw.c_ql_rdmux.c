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
struct TYPE_3__ {int select_addr; int select_value; int read_addr; int op_count; scalar_t__ select_value_stride; } ;
typedef  TYPE_1__ ql_minidump_entry_mux_t ;

/* Variables and functions */
 int ql_rdwr_indreg32 (int /*<<< orphan*/ *,int,int*,int) ; 

__attribute__((used)) static uint32_t 
ql_rdmux(qla_host_t *ha,
	ql_minidump_entry_mux_t *muxEntry,
	uint32_t *data_buff)
{
	int ret;
	int loop_cnt;
	uint32_t read_value, sel_value;
	uint32_t read_addr, select_addr;

	select_addr = muxEntry->select_addr;
	sel_value = muxEntry->select_value;
	read_addr = muxEntry->read_addr;

	for (loop_cnt = 0; loop_cnt < muxEntry->op_count; loop_cnt++) {

		ret = ql_rdwr_indreg32(ha, select_addr, &sel_value, 0);
		if (ret)
			return (0);

		ret = ql_rdwr_indreg32(ha, read_addr, &read_value, 1);
		if (ret)
			return (0);

		*data_buff++ = sel_value;
		*data_buff++ = read_value;

		sel_value += muxEntry->select_value_stride;
	}

	return (loop_cnt * (2 * sizeof(uint32_t)));
}