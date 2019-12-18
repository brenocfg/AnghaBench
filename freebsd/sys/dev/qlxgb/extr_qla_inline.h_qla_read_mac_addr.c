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
typedef  int uint32_t ;
struct TYPE_5__ {void** mac_addr; } ;
struct TYPE_6__ {int pci_func; TYPE_1__ hw; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int Q8_CRB_MAC_BLOCK_START ; 
 int READ_REG32 (TYPE_2__*,int) ; 

__attribute__((used)) static __inline void
qla_read_mac_addr(qla_host_t *ha)
{
	uint32_t mac_crb_addr;
	uint32_t mac_lo;
	uint32_t mac_hi;
	uint8_t	*macp;

	mac_crb_addr = Q8_CRB_MAC_BLOCK_START +
		(((ha->pci_func >> 1) * 3) << 2) + ((ha->pci_func & 0x01) << 2);

	mac_lo = READ_REG32(ha, mac_crb_addr);
	mac_hi = READ_REG32(ha, (mac_crb_addr + 0x4));

	if (ha->pci_func & 0x01) {
		mac_lo = mac_lo >> 16;

		macp = (uint8_t *)&mac_lo;

		ha->hw.mac_addr[5] = macp[0];
		ha->hw.mac_addr[4] = macp[1];

		macp = (uint8_t *)&mac_hi;

		ha->hw.mac_addr[3] = macp[0];
		ha->hw.mac_addr[2] = macp[1];
		ha->hw.mac_addr[1] = macp[2];
		ha->hw.mac_addr[0] = macp[3];
	} else {
		macp = (uint8_t *)&mac_lo;

		ha->hw.mac_addr[5] = macp[0];
		ha->hw.mac_addr[4] = macp[1];
		ha->hw.mac_addr[3] = macp[2];
		ha->hw.mac_addr[2] = macp[3];

		macp = (uint8_t *)&mac_hi;

		ha->hw.mac_addr[1] = macp[0];
		ha->hw.mac_addr[0] = macp[1];
	}
	return;
}