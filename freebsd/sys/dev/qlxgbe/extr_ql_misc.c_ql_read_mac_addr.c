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
typedef  void* uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {void** mac_addr; } ;
struct TYPE_6__ {int pci_func; TYPE_1__ hw; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 scalar_t__ Q8_BOARD_CONFIG_MAC0_LO ; 
 scalar_t__ Q8_BOARD_CONFIG_OFFSET ; 
 int /*<<< orphan*/  ql_rd_flash32 (TYPE_2__*,scalar_t__,scalar_t__*) ; 

void
ql_read_mac_addr(qla_host_t *ha)
{
	uint8_t *macp;
	uint32_t mac_lo;
	uint32_t mac_hi;
	uint32_t flash_off;

	flash_off = Q8_BOARD_CONFIG_OFFSET + Q8_BOARD_CONFIG_MAC0_LO +
			(ha->pci_func << 3);
	ql_rd_flash32(ha, flash_off, &mac_lo);

	flash_off += 4;
	ql_rd_flash32(ha, flash_off, &mac_hi);

	macp = (uint8_t *)&mac_lo;
	ha->hw.mac_addr[5] = macp[0];
	ha->hw.mac_addr[4] = macp[1];
	ha->hw.mac_addr[3] = macp[2];
	ha->hw.mac_addr[2] = macp[3];
 
	macp = (uint8_t *)&mac_hi;
	ha->hw.mac_addr[1] = macp[0];
	ha->hw.mac_addr[0] = macp[1];

	//device_printf(ha->pci_dev, "%s: %02x:%02x:%02x:%02x:%02x:%02x\n",
	//	__func__, ha->hw.mac_addr[0], ha->hw.mac_addr[1],
	//	ha->hw.mac_addr[2], ha->hw.mac_addr[3],
	//	ha->hw.mac_addr[4], ha->hw.mac_addr[5]);

        return;
}