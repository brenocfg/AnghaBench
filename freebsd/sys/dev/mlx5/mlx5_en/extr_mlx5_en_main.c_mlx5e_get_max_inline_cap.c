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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u16 ;
struct mlx5e_tx_wqe {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5E_MAX_TX_INLINE ; 
 unsigned int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_bf_reg_size ; 

__attribute__((used)) static u16
mlx5e_get_max_inline_cap(struct mlx5_core_dev *mdev)
{
	uint32_t bf_buf_size = (1U << MLX5_CAP_GEN(mdev, log_bf_reg_size)) / 2U;

	bf_buf_size -= sizeof(struct mlx5e_tx_wqe) - 2;

	/* verify against driver hardware limit */
	if (bf_buf_size > MLX5E_MAX_TX_INLINE)
		bf_buf_size = MLX5E_MAX_TX_INLINE;

	return (bf_buf_size);
}