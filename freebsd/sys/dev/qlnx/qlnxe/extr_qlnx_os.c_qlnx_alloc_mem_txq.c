#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union eth_tx_bd_types {int dummy; } eth_tx_bd_types ;
struct sw_tx_bd {int dummy; } ;
struct qlnx_tx_queue {int num_tx_buffers; int /*<<< orphan*/  tx_pbl; int /*<<< orphan*/ * sw_tx_ring; } ;
struct qlnx_fastpath {int dummy; } ;
struct ecore_dev {int dummy; } ;
struct TYPE_4__ {struct ecore_dev cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_CHAIN_CNT_TYPE_U16 ; 
 int /*<<< orphan*/  ECORE_CHAIN_MODE_PBL ; 
 int /*<<< orphan*/  ECORE_CHAIN_USE_TO_CONSUME_PRODUCE ; 
 int ECORE_SUCCESS ; 
 int ENOMEM ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int ecore_chain_alloc (struct ecore_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_free_mem_txq (TYPE_1__*,struct qlnx_fastpath*,struct qlnx_tx_queue*) ; 

__attribute__((used)) static int
qlnx_alloc_mem_txq(qlnx_host_t *ha, struct qlnx_fastpath *fp, 
	struct qlnx_tx_queue *txq)
{
        int			ret = ECORE_SUCCESS;
        union eth_tx_bd_types	*p_virt;
	struct ecore_dev	*cdev;

	cdev = &ha->cdev;

	bzero((void *)&txq->sw_tx_ring[0],
		(sizeof (struct sw_tx_bd) * TX_RING_SIZE));

        /* Allocate the real Tx ring to be used by FW */
        ret = ecore_chain_alloc(cdev,
                        ECORE_CHAIN_USE_TO_CONSUME_PRODUCE,
                        ECORE_CHAIN_MODE_PBL,
			ECORE_CHAIN_CNT_TYPE_U16,
                        TX_RING_SIZE,
                        sizeof(*p_virt),
                        &txq->tx_pbl, NULL);

        if (ret != ECORE_SUCCESS) {
                goto err;
        }

	txq->num_tx_buffers = TX_RING_SIZE;

        return 0;

err:
        qlnx_free_mem_txq(ha, fp, txq);
        return -ENOMEM;
}