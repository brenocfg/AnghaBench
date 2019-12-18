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
typedef  int u16 ;
struct TYPE_2__ {int sz_m1; int cc; int log_sz; } ;
struct mlx5e_cq {TYPE_1__ wq; } ;
struct mlx5_mini_cqe8 {int /*<<< orphan*/  rx_hash_result; int /*<<< orphan*/  byte_cnt; } ;
struct mlx5_cqe64 {int op_own; scalar_t__ check_sum; int /*<<< orphan*/  rss_hash_result; int /*<<< orphan*/  wqe_counter; int /*<<< orphan*/  byte_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int) ; 

__attribute__((used)) static inline void
mlx5e_decompress_cqe(struct mlx5e_cq *cq, struct mlx5_cqe64 *title,
    struct mlx5_mini_cqe8 *mini,
    u16 wqe_counter, int i)
{
	/*
	 * NOTE: The fields which are not set here are copied from the
	 * initial and common title. See memcpy() in
	 * mlx5e_write_cqe_slot().
	 */
	title->byte_cnt = mini->byte_cnt;
	title->wqe_counter = cpu_to_be16((wqe_counter + i) & cq->wq.sz_m1);
	title->rss_hash_result = mini->rx_hash_result;
	/*
	 * Since we use MLX5_CQE_FORMAT_HASH when creating the RX CQ,
	 * the value of the checksum should be ignored.
	 */
	title->check_sum = 0;
	title->op_own = (title->op_own & 0xf0) |
	    (((cq->wq.cc + i) >> cq->wq.log_sz) & 1);
}