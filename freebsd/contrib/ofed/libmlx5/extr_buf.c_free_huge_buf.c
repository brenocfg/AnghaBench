#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_context {int /*<<< orphan*/  hugetlb_lock; int /*<<< orphan*/  hugetlb_list; } ;
struct mlx5_buf {int length; TYPE_1__* hmem; int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int MLX5_Q_CHUNK_SIZE ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_free_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free_huge_mem (TYPE_1__*) ; 
 int /*<<< orphan*/  mlx5_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_huge_buf(struct mlx5_context *ctx, struct mlx5_buf *buf)
{
	int nchunk;

	nchunk = buf->length / MLX5_Q_CHUNK_SIZE;
	mlx5_spin_lock(&ctx->hugetlb_lock);
	bitmap_free_range(&buf->hmem->bitmap, buf->base, nchunk);
	if (bitmap_empty(&buf->hmem->bitmap)) {
		TAILQ_REMOVE(&ctx->hugetlb_list, buf->hmem, entry);
		mlx5_spin_unlock(&ctx->hugetlb_lock);
		free_huge_mem(buf->hmem);
	} else
		mlx5_spin_unlock(&ctx->hugetlb_lock);
}