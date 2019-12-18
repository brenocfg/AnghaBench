#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union eth_rx_cqe {int dummy; } eth_rx_cqe ;
struct sw_rx_data {int dummy; } ;
struct lro_ctrl {struct ifnet* ifp; } ;
struct qlnx_rx_queue {int num_rx_buffers; int rxq_id; struct lro_ctrl lro; int /*<<< orphan*/ * tpa_info; int /*<<< orphan*/  rx_buf_size; int /*<<< orphan*/  rx_comp_ring; int /*<<< orphan*/  rx_bd_ring; int /*<<< orphan*/ * sw_rx_ring; } ;
struct ifnet {int dummy; } ;
struct eth_rx_bd {int dummy; } ;
struct ecore_dev {int dummy; } ;
struct TYPE_7__ {struct ifnet* ifp; int /*<<< orphan*/  rx_buf_size; struct ecore_dev cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_CHAIN_CNT_TYPE_U16 ; 
 int /*<<< orphan*/  ECORE_CHAIN_MODE_NEXT_PTR ; 
 int /*<<< orphan*/  ECORE_CHAIN_MODE_PBL ; 
 int /*<<< orphan*/  ECORE_CHAIN_USE_TO_CONSUME ; 
 int /*<<< orphan*/  ECORE_CHAIN_USE_TO_CONSUME_PRODUCE ; 
 int ENOMEM ; 
 int ETH_TPA_MAX_AGGS_NUM ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_1__*,char*,...) ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int ecore_chain_alloc (struct ecore_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int qlnx_alloc_rx_buffer (TYPE_1__*,struct qlnx_rx_queue*) ; 
 int qlnx_alloc_tpa_mbuf (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_free_mem_rxq (TYPE_1__*,struct qlnx_rx_queue*) ; 
 scalar_t__ tcp_lro_init (struct lro_ctrl*) ; 
 scalar_t__ tcp_lro_init_args (struct lro_ctrl*,struct ifnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
qlnx_alloc_mem_rxq(qlnx_host_t *ha, struct qlnx_rx_queue *rxq)
{
        int			i, rc, num_allocated;
	struct ifnet		*ifp;
	struct ecore_dev	 *cdev;

	cdev = &ha->cdev;
	ifp = ha->ifp;

        rxq->num_rx_buffers = RX_RING_SIZE;

	rxq->rx_buf_size = ha->rx_buf_size;

        /* Allocate the parallel driver ring for Rx buffers */
	bzero((void *)&rxq->sw_rx_ring[0],
		(sizeof (struct sw_rx_data) * RX_RING_SIZE));

        /* Allocate FW Rx ring  */

        rc = ecore_chain_alloc(cdev,
			ECORE_CHAIN_USE_TO_CONSUME_PRODUCE,
			ECORE_CHAIN_MODE_NEXT_PTR,
			ECORE_CHAIN_CNT_TYPE_U16,
			RX_RING_SIZE,
			sizeof(struct eth_rx_bd),
			&rxq->rx_bd_ring, NULL);

        if (rc)
                goto err;

        /* Allocate FW completion ring */
        rc = ecore_chain_alloc(cdev,
                        ECORE_CHAIN_USE_TO_CONSUME,
                        ECORE_CHAIN_MODE_PBL,
			ECORE_CHAIN_CNT_TYPE_U16,
                        RX_RING_SIZE,
                        sizeof(union eth_rx_cqe),
                        &rxq->rx_comp_ring, NULL);

        if (rc)
                goto err;

        /* Allocate buffers for the Rx ring */

	for (i = 0; i < ETH_TPA_MAX_AGGS_NUM; i++) {
		rc = qlnx_alloc_tpa_mbuf(ha, rxq->rx_buf_size,
			&rxq->tpa_info[i]);
                if (rc)
                        break;

	}

        for (i = 0; i < rxq->num_rx_buffers; i++) {
                rc = qlnx_alloc_rx_buffer(ha, rxq);
                if (rc)
                        break;
        }
        num_allocated = i;
        if (!num_allocated) {
		QL_DPRINT1(ha, "Rx buffers allocation failed\n");
                goto err;
        } else if (num_allocated < rxq->num_rx_buffers) {
		QL_DPRINT1(ha, "Allocated less buffers than"
			" desired (%d allocated)\n", num_allocated);
        }

#ifdef QLNX_SOFT_LRO

	{
		struct lro_ctrl *lro;

		lro = &rxq->lro;

#if (__FreeBSD_version >= 1100101) || (defined QLNX_QSORT_LRO)
		if (tcp_lro_init_args(lro, ifp, 0, rxq->num_rx_buffers)) {
			QL_DPRINT1(ha, "tcp_lro_init[%d] failed\n",
				   rxq->rxq_id);
			goto err;
		}
#else
		if (tcp_lro_init(lro)) {
			QL_DPRINT1(ha, "tcp_lro_init[%d] failed\n",
				   rxq->rxq_id);
			goto err;
		}
#endif /* #if (__FreeBSD_version >= 1100101) || (defined QLNX_QSORT_LRO) */

		lro->ifp = ha->ifp;
	}
#endif /* #ifdef QLNX_SOFT_LRO */
        return 0;

err:
        qlnx_free_mem_rxq(ha, rxq);
        return -ENOMEM;
}