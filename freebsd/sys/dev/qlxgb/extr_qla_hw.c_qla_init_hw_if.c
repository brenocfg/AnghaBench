#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_18__ {TYPE_1__* sds_ring; } ;
struct TYPE_21__ {int num_sds_rings; int* mac_addr; TYPE_4__* rx_cntxt_rsp; scalar_t__ rxj_next; scalar_t__ rx_next; scalar_t__ rxj_in; scalar_t__ rx_in; TYPE_2__ dma_buf; } ;
struct TYPE_22__ {TYPE_5__ hw; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_6__ qla_host_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_19__ {int /*<<< orphan*/  cntxt_id; } ;
struct TYPE_20__ {TYPE_3__ rx_rsp; } ;
struct TYPE_17__ {int /*<<< orphan*/  size; int /*<<< orphan*/  dma_b; } ;

/* Variables and functions */
 scalar_t__ NUM_RX_DESCRIPTORS ; 
 scalar_t__ NUM_RX_JUMBO_DESCRIPTORS ; 
 int /*<<< orphan*/  QL_ENABLE_INTERRUPTS (TYPE_6__*,int) ; 
 int /*<<< orphan*/  QL_UPDATE_RDS_PRODUCER_INDEX (TYPE_6__*,int,scalar_t__) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla_config_intr_coalesce (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla_config_mac_addr (TYPE_6__*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qla_config_rss (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla_del_rcv_cntxt (TYPE_6__*) ; 
 int /*<<< orphan*/  qla_get_hw_caps (TYPE_6__*) ; 
 scalar_t__ qla_init_rcv_cntxt (TYPE_6__*) ; 
 scalar_t__ qla_init_xmt_cntxt (TYPE_6__*) ; 

int
qla_init_hw_if(qla_host_t *ha)
{
	device_t	dev;
	int		i;
	uint8_t		bcast_mac[6];

	qla_get_hw_caps(ha);

	dev = ha->pci_dev;

	for (i = 0; i < ha->hw.num_sds_rings; i++) {
		bzero(ha->hw.dma_buf.sds_ring[i].dma_b,
			ha->hw.dma_buf.sds_ring[i].size);
	}
	/*
	 * Create Receive Context
	 */
	if (qla_init_rcv_cntxt(ha)) {
		return (-1);
	}

	ha->hw.rx_next = NUM_RX_DESCRIPTORS - 2;
	ha->hw.rxj_next = NUM_RX_JUMBO_DESCRIPTORS - 2;
	ha->hw.rx_in = ha->hw.rxj_in = 0;

	/* Update the RDS Producer Indices */
	QL_UPDATE_RDS_PRODUCER_INDEX(ha, 0, ha->hw.rx_next);
	QL_UPDATE_RDS_PRODUCER_INDEX(ha, 1, ha->hw.rxj_next);

	/*
	 * Create Transmit Context
	 */
	if (qla_init_xmt_cntxt(ha)) {
		qla_del_rcv_cntxt(ha);
		return (-1);
	}

	qla_config_mac_addr(ha, ha->hw.mac_addr,
		(ha->hw.rx_cntxt_rsp)->rx_rsp.cntxt_id, 1);

	bcast_mac[0] = 0xFF; bcast_mac[1] = 0xFF; bcast_mac[2] = 0xFF;
	bcast_mac[3] = 0xFF; bcast_mac[4] = 0xFF; bcast_mac[5] = 0xFF;
	qla_config_mac_addr(ha, bcast_mac,
		(ha->hw.rx_cntxt_rsp)->rx_rsp.cntxt_id, 1);

	qla_config_rss(ha, (ha->hw.rx_cntxt_rsp)->rx_rsp.cntxt_id);

	qla_config_intr_coalesce(ha, (ha->hw.rx_cntxt_rsp)->rx_rsp.cntxt_id, 0);

	for (i = 0; i < ha->hw.num_sds_rings; i++)
		QL_ENABLE_INTERRUPTS(ha, i);

	return (0);
}