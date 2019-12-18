#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5_fpga_dma_buf {int dummy; } ;
struct mlx5_fpga_conn {int dummy; } ;

/* Variables and functions */
 int mlx5_fpga_conn_send (struct mlx5_fpga_conn*,struct mlx5_fpga_dma_buf*) ; 

int mlx5_fpga_sbu_conn_sendmsg(struct mlx5_fpga_conn *conn,
			       struct mlx5_fpga_dma_buf *buf)
{
#ifdef NOT_YET
	/* XXXKIB */
	return mlx5_fpga_conn_send(conn, buf);
#else
	return (0);
#endif
}