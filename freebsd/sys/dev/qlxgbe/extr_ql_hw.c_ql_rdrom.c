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
typedef  int /*<<< orphan*/  value ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;
struct TYPE_3__ {int read_addr; int read_data_size; } ;
typedef  TYPE_1__ ql_minidump_entry_rdrom_t ;

/* Variables and functions */
 int ql_rd_flash32 (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static uint32_t 
ql_rdrom(qla_host_t *ha,
	ql_minidump_entry_rdrom_t *romEntry,
	uint32_t *data_buff)
{
	int ret;
	int i, loop_cnt;
	uint32_t addr;
	uint32_t value;

	addr = romEntry->read_addr;
	loop_cnt = romEntry->read_data_size; /* This is size in bytes */
	loop_cnt /= sizeof(value);

	for (i = 0; i < loop_cnt; i++) {

		ret = ql_rd_flash32(ha, addr, &value);
		if (ret)
			return (0);

		*data_buff++ = value;
		addr += sizeof(value);
	}

	return (loop_cnt * sizeof(value));
}