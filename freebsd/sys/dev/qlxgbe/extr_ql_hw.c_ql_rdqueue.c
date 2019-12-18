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
struct TYPE_3__ {int read_addr_cnt; int read_addr_stride; int select_addr; int op_count; int read_addr; int queue_id_stride; } ;
typedef  TYPE_1__ ql_minidump_entry_queue_t ;

/* Variables and functions */
 int ql_rdwr_indreg32 (int /*<<< orphan*/ *,int,int*,int) ; 

__attribute__((used)) static uint32_t 
ql_rdqueue(qla_host_t *ha,
	ql_minidump_entry_queue_t *queueEntry,
	uint32_t *data_buff)
{
	int ret;
	int loop_cnt, k;
	uint32_t read_value;
	uint32_t read_addr, read_stride, select_addr;
	uint32_t queue_id, read_cnt;

	read_cnt = queueEntry->read_addr_cnt;
	read_stride = queueEntry->read_addr_stride;
	select_addr = queueEntry->select_addr;

	for (loop_cnt = 0, queue_id = 0; loop_cnt < queueEntry->op_count;
		loop_cnt++) {

		ret = ql_rdwr_indreg32(ha, select_addr, &queue_id, 0);
		if (ret)
			return (0);

		read_addr = queueEntry->read_addr;

		for (k = 0; k < read_cnt; k++) {

			ret = ql_rdwr_indreg32(ha, read_addr, &read_value, 1);
			if (ret)
				return (0);

			*data_buff++ = read_value;
			read_addr += read_stride;
		}

		queue_id += queueEntry->queue_id_stride;
	}

	return (loop_cnt * (read_cnt * sizeof(uint32_t)));
}