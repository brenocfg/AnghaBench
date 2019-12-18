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
typedef  int /*<<< orphan*/  uint32_t ;
struct mlx4_context {scalar_t__ uar; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_PAIR_TO_64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmio_writeq (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlx4_write64(uint32_t val[2], struct mlx4_context *ctx, int offset)
{
	mmio_writeq((unsigned long)(ctx->uar + offset), MLX4_PAIR_TO_64(val));
}