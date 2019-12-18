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
struct TYPE_6__ {int txr_idx; int /*<<< orphan*/ * tx_br; int /*<<< orphan*/  tx_mtx; int /*<<< orphan*/  tx_mtx_name; } ;
typedef  TYPE_1__ qla_tx_fp_t ;
struct TYPE_7__ {int pci_func; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NUM_TX_DESCRIPTORS ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * buf_ring_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 

__attribute__((used)) static int
qla_alloc_tx_br(qla_host_t *ha, qla_tx_fp_t *fp)
{
        snprintf(fp->tx_mtx_name, sizeof(fp->tx_mtx_name),
                "qla%d_fp%d_tx_mq_lock", ha->pci_func, fp->txr_idx);

        mtx_init(&fp->tx_mtx, fp->tx_mtx_name, NULL, MTX_DEF);

        fp->tx_br = buf_ring_alloc(NUM_TX_DESCRIPTORS, M_DEVBUF,
                                   M_NOWAIT, &fp->tx_mtx);
        if (fp->tx_br == NULL) {
            QL_DPRINT1(ha, (ha->pci_dev, "buf_ring_alloc failed for "
                " fp[%d, %d]\n", ha->pci_func, fp->txr_idx));
            return (-ENOMEM);
        }
        return 0;
}