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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  qla_host_t ;
struct TYPE_5__ {int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  opcode; int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {int flags; int max_rcv_pkts; int max_rcv_usecs; int max_snd_pkts; int max_snd_usecs; int usecs_to; int /*<<< orphan*/  sds_ring_bitmask; int /*<<< orphan*/  timer_type; TYPE_1__ hdr; } ;
typedef  TYPE_2__ qla_fw_cds_config_intr_coalesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q8_FWCD_CNTRL_REQ ; 
 int /*<<< orphan*/  Q8_FWCD_OPCODE_CONFIG_INTR_COALESCING ; 
 int /*<<< orphan*/  Q8_FWCMD_INTR_COALESC_SDS_RING_0 ; 
 int /*<<< orphan*/  Q8_FWCMD_INTR_COALESC_TIMER_PERIODIC ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int qla_fw_cmd (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static int
qla_config_intr_coalesce(qla_host_t *ha, uint16_t cntxt_id, int tenable)
{
	qla_fw_cds_config_intr_coalesc_t intr_coalesce;
	int ret;

	bzero(&intr_coalesce, sizeof(qla_fw_cds_config_intr_coalesc_t));

	intr_coalesce.hdr.cmd = Q8_FWCD_CNTRL_REQ;
	intr_coalesce.hdr.opcode = Q8_FWCD_OPCODE_CONFIG_INTR_COALESCING;
	intr_coalesce.hdr.cntxt_id = cntxt_id;
	
	intr_coalesce.flags = 0x04;
	intr_coalesce.max_rcv_pkts = 256;
	intr_coalesce.max_rcv_usecs = 3;
	intr_coalesce.max_snd_pkts = 64;
	intr_coalesce.max_snd_usecs = 4;

	if (tenable) {
		intr_coalesce.usecs_to = 1000; /* 1 millisecond */
		intr_coalesce.timer_type = Q8_FWCMD_INTR_COALESC_TIMER_PERIODIC;
		intr_coalesce.sds_ring_bitmask =
			Q8_FWCMD_INTR_COALESC_SDS_RING_0;
	}

	ret = qla_fw_cmd(ha, &intr_coalesce,
			sizeof(qla_fw_cds_config_intr_coalesc_t));

	return ret;
}