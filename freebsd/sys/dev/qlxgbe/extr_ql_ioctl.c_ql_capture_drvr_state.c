#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/  dma_b; } ;
struct TYPE_15__ {TYPE_1__* sds_ring; TYPE_3__* rds_ring; TYPE_2__ tx_ring; } ;
struct TYPE_16__ {int num_tx_rings; int num_rds_rings; int num_sds_rings; TYPE_4__ dma_buf; int /*<<< orphan*/  xmt_intr_coalesce; int /*<<< orphan*/  rcv_intr_coalesce; int /*<<< orphan*/  link_faults; int /*<<< orphan*/  module_type; int /*<<< orphan*/  link_up; int /*<<< orphan*/  cable_oui; int /*<<< orphan*/  cable_length; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/ * drvr_state; } ;
struct TYPE_17__ {TYPE_5__ hw; } ;
typedef  TYPE_6__ qla_host_t ;
typedef  int /*<<< orphan*/  qla_drvr_state_tx_t ;
typedef  int /*<<< orphan*/  qla_drvr_state_sds_t ;
typedef  int /*<<< orphan*/  qla_drvr_state_rx_t ;
struct TYPE_18__ {int saved; int tx_state_offset; int rx_state_offset; int sds_state_offset; int txr_offset; int num_tx_rings; int txr_size; int txr_entries; int rxr_offset; int rxr_size; int rxr_entries; int num_rx_rings; int sds_offset; int sds_ring_size; int sds_entries; int num_sds_rings; int /*<<< orphan*/  xmt_intr_coalesce; int /*<<< orphan*/  rcv_intr_coalesce; int /*<<< orphan*/  link_faults; int /*<<< orphan*/  module_type; int /*<<< orphan*/  link_up; int /*<<< orphan*/  cable_oui; int /*<<< orphan*/  cable_length; int /*<<< orphan*/  link_speed; int /*<<< orphan*/ * mac_addr; int /*<<< orphan*/  drvr_version_build; int /*<<< orphan*/  drvr_version_minor; scalar_t__ drvr_version_major; int /*<<< orphan*/  usec_ts; } ;
typedef  TYPE_7__ qla_drvr_state_hdr_t ;
typedef  int /*<<< orphan*/  q80_tx_cmd_t ;
typedef  int /*<<< orphan*/  q80_stat_desc_t ;
typedef  int /*<<< orphan*/  q80_recv_desc_t ;
struct TYPE_14__ {int /*<<< orphan*/  dma_b; } ;
struct TYPE_12__ {int /*<<< orphan*/  dma_b; } ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int NUM_RX_DESCRIPTORS ; 
 int NUM_STATUS_DESCRIPTORS ; 
 int NUM_TX_DESCRIPTORS ; 
 int /*<<< orphan*/  QLA_VERSION_BUILD ; 
 scalar_t__ QLA_VERSION_MAJOR ; 
 int /*<<< orphan*/  QLA_VERSION_MINOR ; 
 void* QL_ALIGN (int,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ql_get_rx_state (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_get_sds_state (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_get_tx_state (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_get_usec_timestamp () ; 

void
ql_capture_drvr_state(qla_host_t *ha)
{
	uint8_t *state_buffer;
	uint8_t *ptr;
	qla_drvr_state_hdr_t *hdr;
	uint32_t size;
	int i;

	state_buffer =  ha->hw.drvr_state;

	if (state_buffer == NULL)
		return;

	hdr = (qla_drvr_state_hdr_t *)state_buffer;
	
	hdr->saved = 0;

	if (hdr->drvr_version_major) {
		hdr->saved = 1;
		return;
	}

	hdr->usec_ts = qla_get_usec_timestamp();

	hdr->drvr_version_major = QLA_VERSION_MAJOR;
	hdr->drvr_version_minor = QLA_VERSION_MINOR;
	hdr->drvr_version_build = QLA_VERSION_BUILD;

	bcopy(ha->hw.mac_addr, hdr->mac_addr, ETHER_ADDR_LEN);

	hdr->link_speed = ha->hw.link_speed;
	hdr->cable_length = ha->hw.cable_length;
	hdr->cable_oui = ha->hw.cable_oui;
	hdr->link_up = ha->hw.link_up;
	hdr->module_type = ha->hw.module_type;
	hdr->link_faults = ha->hw.link_faults;
	hdr->rcv_intr_coalesce = ha->hw.rcv_intr_coalesce;
	hdr->xmt_intr_coalesce = ha->hw.xmt_intr_coalesce;

	size = sizeof (qla_drvr_state_hdr_t);
	hdr->tx_state_offset = QL_ALIGN(size, 64);

	ptr = state_buffer + hdr->tx_state_offset;

	ql_get_tx_state(ha, (qla_drvr_state_tx_t *)ptr);

	size =  ha->hw.num_tx_rings * (sizeof (qla_drvr_state_tx_t));
	hdr->rx_state_offset = hdr->tx_state_offset + QL_ALIGN(size, 64);
	ptr = state_buffer + hdr->rx_state_offset;

	ql_get_rx_state(ha, (qla_drvr_state_rx_t *)ptr);

	size =  ha->hw.num_rds_rings * (sizeof (qla_drvr_state_rx_t));
	hdr->sds_state_offset = hdr->rx_state_offset + QL_ALIGN(size, 64);
	ptr = state_buffer + hdr->sds_state_offset;

	ql_get_sds_state(ha, (qla_drvr_state_sds_t *)ptr);

	size =  ha->hw.num_sds_rings * (sizeof (qla_drvr_state_sds_t));
	hdr->txr_offset = hdr->sds_state_offset + QL_ALIGN(size, 64);
	ptr = state_buffer + hdr->txr_offset;

	hdr->num_tx_rings = ha->hw.num_tx_rings;
	hdr->txr_size = sizeof(q80_tx_cmd_t) * NUM_TX_DESCRIPTORS;
	hdr->txr_entries = NUM_TX_DESCRIPTORS;

	size = hdr->num_tx_rings * hdr->txr_size;
	bcopy(ha->hw.dma_buf.tx_ring.dma_b, ptr, size);

	hdr->rxr_offset = hdr->txr_offset + QL_ALIGN(size, 64);
	ptr = state_buffer + hdr->rxr_offset;

	hdr->rxr_size = sizeof(q80_recv_desc_t) * NUM_RX_DESCRIPTORS;
	hdr->rxr_entries = NUM_RX_DESCRIPTORS;
	hdr->num_rx_rings = ha->hw.num_rds_rings;

	for (i = 0; i < ha->hw.num_rds_rings; i++) {
		bcopy(ha->hw.dma_buf.rds_ring[i].dma_b, ptr, hdr->rxr_size);
		ptr += hdr->rxr_size;
	}

	size = hdr->rxr_size * hdr->num_rx_rings;
	hdr->sds_offset = hdr->rxr_offset + QL_ALIGN(size, 64);
	hdr->sds_ring_size = sizeof(q80_stat_desc_t) * NUM_STATUS_DESCRIPTORS;
	hdr->sds_entries = NUM_STATUS_DESCRIPTORS;
	hdr->num_sds_rings = ha->hw.num_sds_rings;

	ptr = state_buffer + hdr->sds_offset;
	for (i = 0; i < ha->hw.num_sds_rings; i++) {
		bcopy(ha->hw.dma_buf.sds_ring[i].dma_b, ptr, hdr->sds_ring_size);
		ptr += hdr->sds_ring_size;
	}
	return;
}