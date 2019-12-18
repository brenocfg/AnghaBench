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
struct TYPE_2__ {scalar_t__ d64; void** d32; } ;
struct mlx5e_sq {int sqn; TYPE_1__ doorbell; } ;

/* Variables and functions */
 int MLX5_OPCODE_NOP ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  mlx5e_tx_notify_hw (struct mlx5e_sq*,void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlx5e_reset_sq_doorbell_record(struct mlx5e_sq *sq)
{

	sq->doorbell.d32[0] = cpu_to_be32(MLX5_OPCODE_NOP);
	sq->doorbell.d32[1] = cpu_to_be32(sq->sqn << 8);
	mlx5e_tx_notify_hw(sq, sq->doorbell.d32, 0);
	sq->doorbell.d64 = 0;
}