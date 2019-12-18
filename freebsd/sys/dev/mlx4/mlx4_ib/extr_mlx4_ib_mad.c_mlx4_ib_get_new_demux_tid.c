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
struct mlx4_ib_demux_ctx {int /*<<< orphan*/  tid; } ;
typedef  int __be64 ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int cpu_to_be64 (int) ; 

__be64 mlx4_ib_get_new_demux_tid(struct mlx4_ib_demux_ctx *ctx)
{
	return cpu_to_be64(atomic_inc_return(&ctx->tid)) |
		cpu_to_be64(0xff00000000000000LL);
}