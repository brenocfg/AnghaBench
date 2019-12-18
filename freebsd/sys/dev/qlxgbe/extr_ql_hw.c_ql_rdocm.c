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
struct TYPE_3__ {int read_addr; int op_count; scalar_t__ read_addr_stride; } ;
typedef  TYPE_1__ ql_minidump_entry_rdocm_t ;

/* Variables and functions */
 int READ_REG32 (int /*<<< orphan*/ *,int volatile) ; 

__attribute__((used)) static uint32_t 
ql_rdocm(qla_host_t *ha,
	ql_minidump_entry_rdocm_t *ocmEntry,
	uint32_t *data_buff)
{
	int i, loop_cnt;
	volatile uint32_t addr;
	volatile uint32_t value;

	addr = ocmEntry->read_addr;
	loop_cnt = ocmEntry->op_count;

	for (i = 0; i < loop_cnt; i++) {
		value = READ_REG32(ha, addr);
		*data_buff++ = value;
		addr += ocmEntry->read_addr_stride;
	}
	return (loop_cnt * sizeof(value));
}