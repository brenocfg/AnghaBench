#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct sw_rx_data {struct mbuf* data; int /*<<< orphan*/  map; } ;
struct qlnx_rx_queue {size_t sw_rx_cons; TYPE_1__* tpa_info; int /*<<< orphan*/  rx_bd_ring; struct sw_rx_data* sw_rx_ring; } ;
struct qlnx_fastpath {int /*<<< orphan*/  rss_id; int /*<<< orphan*/  err_rx_mp_null; int /*<<< orphan*/  err_rx_tpa_invalid_agg_num; } ;
struct mbuf {scalar_t__ m_len; struct mbuf* m_next; int /*<<< orphan*/  m_flags; } ;
struct eth_fast_path_rx_tpa_cont_cqe {size_t tpa_agg_index; scalar_t__* len_list; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {scalar_t__ rx_buf_size; int /*<<< orphan*/  rx_tag; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_2__ qlnx_host_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {scalar_t__ agg_state; struct mbuf* mpl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int ETH_TPA_CQE_CONT_LEN_LIST_SIZE ; 
 size_t ETH_TPA_MAX_AGGS_NUM ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 void* QLNX_AGG_STATE_ERROR ; 
 scalar_t__ QLNX_AGG_STATE_START ; 
 int /*<<< orphan*/  QL_DPRINT7 (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_chain_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ qlnx_alloc_rx_buffer (TYPE_2__*,struct qlnx_rx_queue*) ; 
 int /*<<< orphan*/  qlnx_reuse_rx_data (struct qlnx_rx_queue*) ; 

__attribute__((used)) static void
qlnx_tpa_cont(qlnx_host_t *ha, struct qlnx_fastpath *fp,
	struct qlnx_rx_queue *rxq,
	struct eth_fast_path_rx_tpa_cont_cqe *cqe)
{
	struct sw_rx_data	*sw_rx_data;
	int			i;
	struct mbuf		*mpf = NULL, *mpl = NULL, *mpc = NULL;
	struct mbuf		*mp;
	uint32_t		agg_index;
	device_t		dev;

	dev = ha->pci_dev;

        QL_DPRINT7(ha, "[%d]: enter\n \
                \t type = 0x%x\n \
                \t tpa_agg_index = 0x%x\n \
                \t len_list[0] = 0x%x\n \
                \t len_list[1] = 0x%x\n \
                \t len_list[2] = 0x%x\n \
                \t len_list[3] = 0x%x\n \
                \t len_list[4] = 0x%x\n \
                \t len_list[5] = 0x%x\n",
                fp->rss_id, cqe->type, cqe->tpa_agg_index,
                cqe->len_list[0], cqe->len_list[1], cqe->len_list[2],
                cqe->len_list[3], cqe->len_list[4], cqe->len_list[5]);

	agg_index = cqe->tpa_agg_index;

	if (agg_index >= ETH_TPA_MAX_AGGS_NUM) {
		QL_DPRINT7(ha, "[%d]: 0\n ", fp->rss_id);
		fp->err_rx_tpa_invalid_agg_num++;
		return;
	}


	for (i = 0; i < ETH_TPA_CQE_CONT_LEN_LIST_SIZE; i++) {

		QL_DPRINT7(ha, "[%d]: 1\n ", fp->rss_id);

		if (cqe->len_list[i] == 0)
			break;

		if (rxq->tpa_info[agg_index].agg_state != 
			QLNX_AGG_STATE_START) {
			qlnx_reuse_rx_data(rxq);
			continue;
		}

		sw_rx_data = &rxq->sw_rx_ring[rxq->sw_rx_cons];
		bus_dmamap_sync(ha->rx_tag, sw_rx_data->map,
			BUS_DMASYNC_POSTREAD);

		mpc = sw_rx_data->data;

		if (mpc == NULL) {

			QL_DPRINT7(ha, "[%d]: mpc = NULL\n", fp->rss_id);

			fp->err_rx_mp_null++;
			if (mpf != NULL)
				m_freem(mpf);
			mpf = mpl = NULL;
			rxq->tpa_info[agg_index].agg_state =
						QLNX_AGG_STATE_ERROR;
			ecore_chain_consume(&rxq->rx_bd_ring);
			rxq->sw_rx_cons =
				(rxq->sw_rx_cons + 1) & (RX_RING_SIZE - 1);
			continue;
		}

		if (qlnx_alloc_rx_buffer(ha, rxq) != 0) {

			QL_DPRINT7(ha, "[%d]: New buffer allocation failed,"
				" dropping incoming packet and reusing its"
				" buffer\n", fp->rss_id);

			qlnx_reuse_rx_data(rxq);

			if (mpf != NULL)
				m_freem(mpf);
			mpf = mpl = NULL;

			rxq->tpa_info[agg_index].agg_state =
						QLNX_AGG_STATE_ERROR;

			ecore_chain_consume(&rxq->rx_bd_ring);
			rxq->sw_rx_cons =
				(rxq->sw_rx_cons + 1) & (RX_RING_SIZE - 1);

			continue;
		}

		mpc->m_flags &= ~M_PKTHDR;
		mpc->m_next = NULL;
		mpc->m_len = cqe->len_list[i];


		if (mpf == NULL) {
			mpf = mpl = mpc;
		} else {
			mpl->m_len = ha->rx_buf_size;
			mpl->m_next = mpc;
			mpl = mpc;
		}

		ecore_chain_consume(&rxq->rx_bd_ring);
		rxq->sw_rx_cons =
			(rxq->sw_rx_cons + 1) & (RX_RING_SIZE - 1);
	}

        QL_DPRINT7(ha, "[%d]: 2\n" "\tmpf = %p mpl = %p\n",
                  fp->rss_id, mpf, mpl);

	if (mpf != NULL) {
		mp = rxq->tpa_info[agg_index].mpl;
		mp->m_len = ha->rx_buf_size;
		mp->m_next = mpf;
		rxq->tpa_info[agg_index].mpl = mpl;
	}

	return;
}