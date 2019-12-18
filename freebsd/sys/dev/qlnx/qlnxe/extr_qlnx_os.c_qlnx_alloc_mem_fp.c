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
struct qlnx_fastpath {int /*<<< orphan*/ * txq; int /*<<< orphan*/  rxq; int /*<<< orphan*/  rss_id; int /*<<< orphan*/  sb_info; } ;
struct TYPE_7__ {scalar_t__ max_frame_size; int num_tc; scalar_t__ rx_buf_size; scalar_t__ rx_jumbo_buf_eq_mtu; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ MCLBYTES ; 
 scalar_t__ MJUM16BYTES ; 
 scalar_t__ MJUM9BYTES ; 
 scalar_t__ MJUMPAGESIZE ; 
 int qlnx_alloc_mem_rxq (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int qlnx_alloc_mem_sb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qlnx_alloc_mem_txq (TYPE_1__*,struct qlnx_fastpath*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnx_free_mem_fp (TYPE_1__*,struct qlnx_fastpath*) ; 

__attribute__((used)) static int
qlnx_alloc_mem_fp(qlnx_host_t *ha, struct qlnx_fastpath *fp)
{
        int	rc, tc;

        rc = qlnx_alloc_mem_sb(ha, fp->sb_info, fp->rss_id);
        if (rc)
                goto err;

	if (ha->rx_jumbo_buf_eq_mtu) {
		if (ha->max_frame_size <= MCLBYTES)
			ha->rx_buf_size = MCLBYTES;
		else if (ha->max_frame_size <= MJUMPAGESIZE)
			ha->rx_buf_size = MJUMPAGESIZE;
		else if (ha->max_frame_size <= MJUM9BYTES)
			ha->rx_buf_size = MJUM9BYTES;
		else if (ha->max_frame_size <= MJUM16BYTES)
			ha->rx_buf_size = MJUM16BYTES;
	} else {
		if (ha->max_frame_size <= MCLBYTES)
			ha->rx_buf_size = MCLBYTES;
		else
			ha->rx_buf_size = MJUMPAGESIZE;
	}

        rc = qlnx_alloc_mem_rxq(ha, fp->rxq);
        if (rc)
                goto err;

        for (tc = 0; tc < ha->num_tc; tc++) {
                rc = qlnx_alloc_mem_txq(ha, fp, fp->txq[tc]);
                if (rc)
                        goto err;
        }

        return 0;

err:
        qlnx_free_mem_fp(ha, fp);
        return -ENOMEM;
}