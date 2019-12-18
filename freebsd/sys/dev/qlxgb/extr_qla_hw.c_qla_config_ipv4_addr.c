#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_11__ {TYPE_4__* rx_cntxt_rsp; } ;
struct TYPE_15__ {TYPE_1__ hw; } ;
typedef  TYPE_5__ qla_host_t ;
struct TYPE_12__ {int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  opcode; int /*<<< orphan*/  cmd; } ;
struct TYPE_16__ {void* ipv4_addr; void* cmd; TYPE_2__ hdr; } ;
typedef  TYPE_6__ qla_config_ipv4_t ;
struct TYPE_13__ {int /*<<< orphan*/  cntxt_id; } ;
struct TYPE_14__ {TYPE_3__ rx_rsp; } ;

/* Variables and functions */
 scalar_t__ Q8_CONFIG_CMD_IP_ENABLE ; 
 int /*<<< orphan*/  Q8_FWCD_CNTRL_REQ ; 
 int /*<<< orphan*/  Q8_FWCD_OPCODE_CONFIG_IPADDR ; 
 int /*<<< orphan*/  bzero (TYPE_6__*,int) ; 
 int /*<<< orphan*/  qla_fw_cmd (TYPE_5__*,TYPE_6__*,int) ; 

void
qla_config_ipv4_addr(qla_host_t *ha, uint32_t ipv4_addr)
{
	qla_config_ipv4_t ip_conf;

	bzero(&ip_conf, sizeof(qla_config_ipv4_t));

	ip_conf.hdr.cmd = Q8_FWCD_CNTRL_REQ;
	ip_conf.hdr.opcode = Q8_FWCD_OPCODE_CONFIG_IPADDR;
	ip_conf.hdr.cntxt_id = (ha->hw.rx_cntxt_rsp)->rx_rsp.cntxt_id;
	
	ip_conf.cmd = (uint64_t)Q8_CONFIG_CMD_IP_ENABLE;
	ip_conf.ipv4_addr = (uint64_t)ipv4_addr;

	(void)qla_fw_cmd(ha, &ip_conf, sizeof(qla_config_ipv4_t));

	return;
}