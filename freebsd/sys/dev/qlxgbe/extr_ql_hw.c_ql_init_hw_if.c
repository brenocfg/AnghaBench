#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_31__ {scalar_t__ rx_next; int /*<<< orphan*/  prod_std; scalar_t__ rx_in; } ;
typedef  TYPE_6__ qla_rdesc_t ;
struct TYPE_28__ {int init_intr_cnxt; int unicast_mac; int bcast_mac; } ;
struct TYPE_27__ {TYPE_1__* sds_ring; } ;
struct TYPE_30__ {size_t num_sds_rings; size_t num_rds_rings; int* mac_addr; int enable_soft_lro; int /*<<< orphan*/  rcv_cntxt_id; scalar_t__ enable_hw_lro; TYPE_3__ flags; scalar_t__ max_tx_segs; TYPE_6__* rds; TYPE_2__ dma_buf; } ;
struct TYPE_32__ {TYPE_5__ hw; TYPE_4__* ifp; int /*<<< orphan*/  max_frame_size; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_7__ qla_host_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_29__ {int if_capenable; } ;
struct TYPE_26__ {int /*<<< orphan*/  size; int /*<<< orphan*/  dma_b; } ;

/* Variables and functions */
 int IFCAP_LRO ; 
 scalar_t__ NUM_RX_DESCRIPTORS ; 
 size_t Q8_MAX_INTR_VECTORS ; 
 int /*<<< orphan*/  QL_ENABLE_INTERRUPTS (TYPE_7__*,size_t) ; 
 int /*<<< orphan*/  QL_UPDATE_RDS_PRODUCER_INDEX (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ql_set_max_mtu (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qla_config_fw_lro (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ qla_config_intr_cntxt (TYPE_7__*,size_t,size_t,int) ; 
 scalar_t__ qla_config_intr_coalesce (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qla_config_mac_addr (TYPE_7__*,int*,int,int) ; 
 scalar_t__ qla_config_rss (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ qla_config_rss_ind_table (TYPE_7__*) ; 
 scalar_t__ qla_config_soft_lro (TYPE_7__*) ; 
 int /*<<< orphan*/  qla_del_rcv_cntxt (TYPE_7__*) ; 
 scalar_t__ qla_hw_add_all_mcast (TYPE_7__*) ; 
 scalar_t__ qla_init_nic_func (TYPE_7__*) ; 
 scalar_t__ qla_init_rcv_cntxt (TYPE_7__*) ; 
 scalar_t__ qla_init_xmt_cntxt (TYPE_7__*) ; 
 scalar_t__ qla_link_event_req (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ qla_query_fw_dcbx_caps (TYPE_7__*) ; 

int
ql_init_hw_if(qla_host_t *ha)
{
	device_t	dev;
	uint32_t	i;
	uint8_t		bcast_mac[6];
	qla_rdesc_t	*rdesc;
	uint32_t	num_msix;

	dev = ha->pci_dev;

	for (i = 0; i < ha->hw.num_sds_rings; i++) {
		bzero(ha->hw.dma_buf.sds_ring[i].dma_b,
			ha->hw.dma_buf.sds_ring[i].size);
	}

	for (i = 0; i < ha->hw.num_sds_rings; ) {

		if ((i + Q8_MAX_INTR_VECTORS) < ha->hw.num_sds_rings)
			num_msix = Q8_MAX_INTR_VECTORS;
		else
			num_msix = ha->hw.num_sds_rings - i;

		if (qla_config_intr_cntxt(ha, i, num_msix, 1)) {

			if (i > 0) {

				num_msix = i;

				for (i = 0; i < num_msix; ) {
					qla_config_intr_cntxt(ha, i,
						Q8_MAX_INTR_VECTORS, 0);
					i += Q8_MAX_INTR_VECTORS;
				}
			}
			return (-1);
		}

		i = i + num_msix;
	}

        ha->hw.flags.init_intr_cnxt = 1;

	/*
	 * Create Receive Context
	 */
	if (qla_init_rcv_cntxt(ha)) {
		return (-1);
	}

	for (i = 0; i < ha->hw.num_rds_rings; i++) {
		rdesc = &ha->hw.rds[i];
		rdesc->rx_next = NUM_RX_DESCRIPTORS - 2;
		rdesc->rx_in = 0;
		/* Update the RDS Producer Indices */
		QL_UPDATE_RDS_PRODUCER_INDEX(ha, rdesc->prod_std,\
			rdesc->rx_next);
	}

	/*
	 * Create Transmit Context
	 */
	if (qla_init_xmt_cntxt(ha)) {
		qla_del_rcv_cntxt(ha);
		return (-1);
	}
	ha->hw.max_tx_segs = 0;

	if (qla_config_mac_addr(ha, ha->hw.mac_addr, 1, 1))
		return(-1);

	ha->hw.flags.unicast_mac = 1;

	bcast_mac[0] = 0xFF; bcast_mac[1] = 0xFF; bcast_mac[2] = 0xFF;
	bcast_mac[3] = 0xFF; bcast_mac[4] = 0xFF; bcast_mac[5] = 0xFF;

	if (qla_config_mac_addr(ha, bcast_mac, 1, 1))
		return (-1);

	ha->hw.flags.bcast_mac = 1;

	/*
	 * program any cached multicast addresses
	 */
	if (qla_hw_add_all_mcast(ha))
		return (-1);

	if (ql_set_max_mtu(ha, ha->max_frame_size, ha->hw.rcv_cntxt_id))
		return (-1);

	if (qla_config_rss(ha, ha->hw.rcv_cntxt_id))
		return (-1);

	if (qla_config_rss_ind_table(ha))
		return (-1);

	if (qla_config_intr_coalesce(ha, ha->hw.rcv_cntxt_id, 0, 1))
		return (-1);

	if (qla_link_event_req(ha, ha->hw.rcv_cntxt_id))
		return (-1);

	if (ha->ifp->if_capenable & IFCAP_LRO) {
		if (ha->hw.enable_hw_lro) {
			ha->hw.enable_soft_lro = 0;

			if (qla_config_fw_lro(ha, ha->hw.rcv_cntxt_id))
				return (-1);
		} else {
			ha->hw.enable_soft_lro = 1;

			if (qla_config_soft_lro(ha))
				return (-1);
		}
	}

        if (qla_init_nic_func(ha))
                return (-1);

        if (qla_query_fw_dcbx_caps(ha))
                return (-1);

	for (i = 0; i < ha->hw.num_sds_rings; i++)
		QL_ENABLE_INTERRUPTS(ha, i);

	return (0);
}