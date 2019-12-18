#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;
struct TYPE_5__ {int read_addr; int read_data_size; } ;
typedef  TYPE_1__ ql_minidump_entry_rdmem_t ;
struct TYPE_6__ {int /*<<< orphan*/  data_uhi; int /*<<< orphan*/  data_ulo; int /*<<< orphan*/  data_hi; int /*<<< orphan*/  data_lo; } ;
typedef  TYPE_2__ q80_offchip_mem_val_t ;

/* Variables and functions */
 int ql_rdwr_offchip_mem (int /*<<< orphan*/ *,int volatile,TYPE_2__*,int) ; 

__attribute__((used)) static uint32_t 
ql_rdmem(qla_host_t *ha,
	ql_minidump_entry_rdmem_t *mem_entry,
	uint32_t *data_buff)
{
	int ret;
        int i, loop_cnt;
        volatile uint32_t addr;
	q80_offchip_mem_val_t val;

        addr = mem_entry->read_addr;

	/* size in bytes / 16 */
        loop_cnt = mem_entry->read_data_size / (sizeof(uint32_t) * 4);

        for (i = 0; i < loop_cnt; i++) {

		ret = ql_rdwr_offchip_mem(ha, (addr & 0x0ffffffff), &val, 1);
		if (ret)
			return (0);

                *data_buff++ = val.data_lo;
                *data_buff++ = val.data_hi;
                *data_buff++ = val.data_ulo;
                *data_buff++ = val.data_uhi;

                addr += (sizeof(uint32_t) * 4);
        }

        return (loop_cnt * (sizeof(uint32_t) * 4));
}