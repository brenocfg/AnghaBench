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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  opcode; int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; TYPE_1__ hdr; } ;
typedef  TYPE_2__ qla_set_mac_rcv_mode_t ;
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q8_FWCD_CNTRL_REQ ; 
 int /*<<< orphan*/  Q8_FWCD_OPCODE_CONFIG_MAC_RCV_MODE ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int qla_fw_cmd (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static int
qla_set_mac_rcv_mode(qla_host_t *ha, uint16_t cntxt_id, uint32_t mode)
{
	qla_set_mac_rcv_mode_t rcv_mode;
	int ret;

	bzero(&rcv_mode, sizeof(qla_set_mac_rcv_mode_t));

	rcv_mode.hdr.cmd = Q8_FWCD_CNTRL_REQ;
	rcv_mode.hdr.opcode = Q8_FWCD_OPCODE_CONFIG_MAC_RCV_MODE;
	rcv_mode.hdr.cntxt_id = cntxt_id;
	
	rcv_mode.mode = mode;

	ret = qla_fw_cmd(ha, &rcv_mode, sizeof(qla_set_mac_rcv_mode_t));

	return ret;
}