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
struct mlx5_context {int dummy; } ;
struct mlx5_buf {int /*<<< orphan*/  length; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_dofork_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5_free_buf_contig(struct mlx5_context *mctx, struct mlx5_buf *buf)
{
	ibv_dofork_range(buf->buf, buf->length);
	munmap(buf->buf, buf->length);
}