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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;
struct TYPE_3__ {int /*<<< orphan*/  data_uhi; int /*<<< orphan*/  data_ulo; int /*<<< orphan*/  data_hi; int /*<<< orphan*/  data_lo; } ;
typedef  TYPE_1__ offchip_mem_val_t ;

/* Variables and functions */
 int /*<<< orphan*/  qla_rd_flash32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_rdwr_offchip_mem (int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla_load_fw_from_flash(qla_host_t *ha)
{
	uint64_t mem_off	= 0x10000;
	uint32_t flash_off	= 0x10000;
	uint32_t count;
	offchip_mem_val_t val;


	/* only bootloader needs to be loaded into memory */
	for (count = 0; count < 0x20000 ; ) {
		qla_rd_flash32(ha, flash_off, &val.data_lo);
		count = count + 4;
		flash_off = flash_off + 4;

		qla_rd_flash32(ha, flash_off, &val.data_hi);
		count = count + 4;
		flash_off = flash_off + 4;

		qla_rd_flash32(ha, flash_off, &val.data_ulo);
		count = count + 4;
		flash_off = flash_off + 4;

		qla_rd_flash32(ha, flash_off, &val.data_uhi);
		count = count + 4;
		flash_off = flash_off + 4;

		qla_rdwr_offchip_mem(ha, mem_off, &val, 0);

		mem_off = mem_off + 16;
	}
	return;
}