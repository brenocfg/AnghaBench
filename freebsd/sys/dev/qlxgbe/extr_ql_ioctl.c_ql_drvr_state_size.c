#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int num_tx_rings; int num_rds_rings; int num_sds_rings; } ;
struct TYPE_5__ {TYPE_1__ hw; } ;
typedef  TYPE_2__ qla_host_t ;
typedef  int /*<<< orphan*/  qla_drvr_state_tx_t ;
typedef  int /*<<< orphan*/  qla_drvr_state_sds_t ;
typedef  int /*<<< orphan*/  qla_drvr_state_rx_t ;
typedef  int /*<<< orphan*/  qla_drvr_state_hdr_t ;
typedef  int /*<<< orphan*/  q80_tx_cmd_t ;
typedef  int /*<<< orphan*/  q80_stat_desc_t ;
typedef  int /*<<< orphan*/  q80_recv_desc_t ;

/* Variables and functions */
 int NUM_RX_DESCRIPTORS ; 
 int NUM_STATUS_DESCRIPTORS ; 
 int NUM_TX_DESCRIPTORS ; 
 int QL_ALIGN (int,int) ; 

__attribute__((used)) static uint32_t
ql_drvr_state_size(qla_host_t *ha)
{
	uint32_t drvr_state_size;
	uint32_t size;

	size = sizeof (qla_drvr_state_hdr_t);
	drvr_state_size = QL_ALIGN(size, 64);

	size =  ha->hw.num_tx_rings * (sizeof (qla_drvr_state_tx_t));
	drvr_state_size += QL_ALIGN(size, 64);

	size =  ha->hw.num_rds_rings * (sizeof (qla_drvr_state_rx_t));
	drvr_state_size += QL_ALIGN(size, 64);

	size =  ha->hw.num_sds_rings * (sizeof (qla_drvr_state_sds_t));
	drvr_state_size += QL_ALIGN(size, 64);

	size = sizeof(q80_tx_cmd_t) * NUM_TX_DESCRIPTORS * ha->hw.num_tx_rings;
	drvr_state_size += QL_ALIGN(size, 64);

	size = sizeof(q80_recv_desc_t) * NUM_RX_DESCRIPTORS * ha->hw.num_rds_rings;
	drvr_state_size += QL_ALIGN(size, 64);

	size = sizeof(q80_stat_desc_t) * NUM_STATUS_DESCRIPTORS *
			ha->hw.num_sds_rings;
	drvr_state_size += QL_ALIGN(size, 64);

	return (drvr_state_size);
}