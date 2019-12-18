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
struct mlx5_buf {int type; } ;

/* Variables and functions */
#define  MLX5_ALLOC_TYPE_ANON 130 
#define  MLX5_ALLOC_TYPE_CONTIG 129 
#define  MLX5_ALLOC_TYPE_HUGE 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_huge_buf (struct mlx5_context*,struct mlx5_buf*) ; 
 int /*<<< orphan*/  mlx5_free_buf (struct mlx5_buf*) ; 
 int /*<<< orphan*/  mlx5_free_buf_contig (struct mlx5_context*,struct mlx5_buf*) ; 
 int /*<<< orphan*/  stderr ; 

int mlx5_free_actual_buf(struct mlx5_context *ctx, struct mlx5_buf *buf)
{
	int err = 0;

	switch (buf->type) {
	case MLX5_ALLOC_TYPE_ANON:
		mlx5_free_buf(buf);
		break;

	case MLX5_ALLOC_TYPE_HUGE:
		free_huge_buf(ctx, buf);
		break;

	case MLX5_ALLOC_TYPE_CONTIG:
		mlx5_free_buf_contig(ctx, buf);
		break;
	default:
		fprintf(stderr, "Bad allocation type\n");
	}

	return err;
}