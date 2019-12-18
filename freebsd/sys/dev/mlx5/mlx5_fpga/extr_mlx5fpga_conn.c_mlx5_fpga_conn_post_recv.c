#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct mlx5_wqe_data_seg {int /*<<< orphan*/  addr; void* lkey; void* byte_count; } ;
struct mlx5_fpga_dma_buf {TYPE_4__* sg; } ;
struct TYPE_14__ {int pc; int cc; int size; struct mlx5_fpga_dma_buf** bufs; } ;
struct TYPE_16__ {void** db; } ;
struct TYPE_13__ {TYPE_8__ rq; } ;
struct TYPE_15__ {TYPE_6__ rq; TYPE_5__ wq; } ;
struct mlx5_fpga_conn {TYPE_7__ qp; TYPE_3__* fdev; } ;
struct TYPE_12__ {int size; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_9__ {int key; } ;
struct TYPE_10__ {TYPE_1__ mkey; } ;
struct TYPE_11__ {TYPE_2__ conn_res; } ;

/* Variables and functions */
 int EBUSY ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int mlx5_fpga_conn_map_buf (struct mlx5_fpga_conn*,struct mlx5_fpga_dma_buf*) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_unmap_buf (struct mlx5_fpga_conn*,struct mlx5_fpga_dma_buf*) ; 
 struct mlx5_wqe_data_seg* mlx5_wq_cyc_get_wqe (TYPE_8__*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx5_fpga_conn_post_recv(struct mlx5_fpga_conn *conn,
				    struct mlx5_fpga_dma_buf *buf)
{
	struct mlx5_wqe_data_seg *data;
	unsigned int ix;
	int err = 0;

	err = mlx5_fpga_conn_map_buf(conn, buf);
	if (unlikely(err))
		goto out;

	if (unlikely(conn->qp.rq.pc - conn->qp.rq.cc >= conn->qp.rq.size)) {
		mlx5_fpga_conn_unmap_buf(conn, buf);
		return -EBUSY;
	}

	ix = conn->qp.rq.pc & (conn->qp.rq.size - 1);
	data = mlx5_wq_cyc_get_wqe(&conn->qp.wq.rq, ix);
	data->byte_count = cpu_to_be32(buf->sg[0].size);
	data->lkey = cpu_to_be32(conn->fdev->conn_res.mkey.key);
	data->addr = cpu_to_be64(buf->sg[0].dma_addr);

	conn->qp.rq.pc++;
	conn->qp.rq.bufs[ix] = buf;

	/* Make sure that descriptors are written before doorbell record. */
	dma_wmb();
	*conn->qp.wq.rq.db = cpu_to_be32(conn->qp.rq.pc & 0xffff);
out:
	return err;
}