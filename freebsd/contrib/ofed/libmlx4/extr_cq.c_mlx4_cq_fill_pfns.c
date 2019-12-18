#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  read_completion_ts; int /*<<< orphan*/  read_dlid_path_bits; int /*<<< orphan*/  read_sl; int /*<<< orphan*/  read_slid; int /*<<< orphan*/  read_src_qp; int /*<<< orphan*/  read_qp_num; int /*<<< orphan*/  read_imm_data; int /*<<< orphan*/  read_byte_len; int /*<<< orphan*/  read_wc_flags; int /*<<< orphan*/  read_vendor_err; int /*<<< orphan*/  read_opcode; int /*<<< orphan*/  next_poll; int /*<<< orphan*/  end_poll; int /*<<< orphan*/  start_poll; } ;
struct mlx4_cq {int flags; TYPE_1__ ibv_cq; } ;
struct ibv_cq_init_attr_ex {int wc_flags; } ;

/* Variables and functions */
 int IBV_WC_EX_WITH_BYTE_LEN ; 
 int IBV_WC_EX_WITH_COMPLETION_TIMESTAMP ; 
 int IBV_WC_EX_WITH_DLID_PATH_BITS ; 
 int IBV_WC_EX_WITH_IMM ; 
 int IBV_WC_EX_WITH_QP_NUM ; 
 int IBV_WC_EX_WITH_SL ; 
 int IBV_WC_EX_WITH_SLID ; 
 int IBV_WC_EX_WITH_SRC_QP ; 
 int MLX4_CQ_FLAGS_SINGLE_THREADED ; 
 int /*<<< orphan*/  mlx4_cq_read_wc_byte_len ; 
 int /*<<< orphan*/  mlx4_cq_read_wc_completion_ts ; 
 int /*<<< orphan*/  mlx4_cq_read_wc_dlid_path_bits ; 
 int /*<<< orphan*/  mlx4_cq_read_wc_flags ; 
 int /*<<< orphan*/  mlx4_cq_read_wc_imm_data ; 
 int /*<<< orphan*/  mlx4_cq_read_wc_opcode ; 
 int /*<<< orphan*/  mlx4_cq_read_wc_qp_num ; 
 int /*<<< orphan*/  mlx4_cq_read_wc_sl ; 
 int /*<<< orphan*/  mlx4_cq_read_wc_slid ; 
 int /*<<< orphan*/  mlx4_cq_read_wc_src_qp ; 
 int /*<<< orphan*/  mlx4_cq_read_wc_vendor_err ; 
 int /*<<< orphan*/  mlx4_end_poll ; 
 int /*<<< orphan*/  mlx4_end_poll_lock ; 
 int /*<<< orphan*/  mlx4_next_poll ; 
 int /*<<< orphan*/  mlx4_start_poll ; 
 int /*<<< orphan*/  mlx4_start_poll_lock ; 

void mlx4_cq_fill_pfns(struct mlx4_cq *cq, const struct ibv_cq_init_attr_ex *cq_attr)
{

	if (cq->flags & MLX4_CQ_FLAGS_SINGLE_THREADED) {
		cq->ibv_cq.start_poll = mlx4_start_poll;
		cq->ibv_cq.end_poll = mlx4_end_poll;
	} else {
		cq->ibv_cq.start_poll = mlx4_start_poll_lock;
		cq->ibv_cq.end_poll = mlx4_end_poll_lock;
	}
	cq->ibv_cq.next_poll = mlx4_next_poll;

	cq->ibv_cq.read_opcode = mlx4_cq_read_wc_opcode;
	cq->ibv_cq.read_vendor_err = mlx4_cq_read_wc_vendor_err;
	cq->ibv_cq.read_wc_flags = mlx4_cq_read_wc_flags;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_BYTE_LEN)
		cq->ibv_cq.read_byte_len = mlx4_cq_read_wc_byte_len;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_IMM)
		cq->ibv_cq.read_imm_data = mlx4_cq_read_wc_imm_data;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_QP_NUM)
		cq->ibv_cq.read_qp_num = mlx4_cq_read_wc_qp_num;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_SRC_QP)
		cq->ibv_cq.read_src_qp = mlx4_cq_read_wc_src_qp;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_SLID)
		cq->ibv_cq.read_slid = mlx4_cq_read_wc_slid;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_SL)
		cq->ibv_cq.read_sl = mlx4_cq_read_wc_sl;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_DLID_PATH_BITS)
		cq->ibv_cq.read_dlid_path_bits = mlx4_cq_read_wc_dlid_path_bits;
	if (cq_attr->wc_flags & IBV_WC_EX_WITH_COMPLETION_TIMESTAMP)
		cq->ibv_cq.read_completion_ts = mlx4_cq_read_wc_completion_ts;
}