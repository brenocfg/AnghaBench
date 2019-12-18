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
struct qlnx_fastpath {int rss_id; int /*<<< orphan*/ * tx_br; int /*<<< orphan*/  tx_mtx; int /*<<< orphan*/  tx_mtx_name; } ;
struct TYPE_4__ {int dev_unit; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  TX_RING_SIZE ; 
 int /*<<< orphan*/ * buf_ring_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 

__attribute__((used)) static int
qlnx_alloc_tx_br(qlnx_host_t *ha, struct qlnx_fastpath *fp)
{
	snprintf(fp->tx_mtx_name, sizeof(fp->tx_mtx_name),
		"qlnx%d_fp%d_tx_mq_lock", ha->dev_unit, fp->rss_id);

	mtx_init(&fp->tx_mtx, fp->tx_mtx_name, NULL, MTX_DEF);

        fp->tx_br = buf_ring_alloc(TX_RING_SIZE, M_DEVBUF,
                                   M_NOWAIT, &fp->tx_mtx);
        if (fp->tx_br == NULL) {
		QL_DPRINT1(ha, "buf_ring_alloc failed for fp[%d, %d]\n",
			ha->dev_unit, fp->rss_id);
		return -ENOMEM;
        }
	return 0;
}