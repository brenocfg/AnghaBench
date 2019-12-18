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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  qla_host_t ;
struct TYPE_5__ {int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  opcode; int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  cmd; TYPE_1__ hdr; } ;
typedef  TYPE_2__ qla_fw_cds_config_mac_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q8_FWCD_ADD_MAC_ADDR ; 
 int /*<<< orphan*/  Q8_FWCD_CNTRL_REQ ; 
 int /*<<< orphan*/  Q8_FWCD_DEL_MAC_ADDR ; 
 int /*<<< orphan*/  Q8_FWCD_OPCODE_CONFIG_MAC_ADDR ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int qla_fw_cmd (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static int
qla_config_mac_addr(qla_host_t *ha, uint8_t *mac_addr, uint16_t cntxt_id,
	uint32_t add_multi)
{
	qla_fw_cds_config_mac_addr_t mac_config;
	int ret;

//	device_printf(ha->pci_dev,
//		"%s: mac_addr %02x:%02x:%02x:%02x:%02x:%02x\n", __func__,
//		mac_addr[0], mac_addr[1], mac_addr[2],
//		mac_addr[3], mac_addr[4], mac_addr[5]);

	bzero(&mac_config, sizeof(qla_fw_cds_config_mac_addr_t));

	mac_config.hdr.cmd = Q8_FWCD_CNTRL_REQ;
	mac_config.hdr.opcode = Q8_FWCD_OPCODE_CONFIG_MAC_ADDR;
	mac_config.hdr.cntxt_id = cntxt_id;
	
	if (add_multi)
		mac_config.cmd = Q8_FWCD_ADD_MAC_ADDR;
	else
		mac_config.cmd = Q8_FWCD_DEL_MAC_ADDR;
	bcopy(mac_addr, mac_config.mac_addr,6); 

	ret = qla_fw_cmd(ha, &mac_config, sizeof(qla_fw_cds_config_mac_addr_t));

	return ret;
}