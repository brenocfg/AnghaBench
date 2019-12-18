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
struct mlx5_buf {int dummy; } ;
typedef  enum mlx5_alloc_type { ____Placeholder_mlx5_alloc_type } mlx5_alloc_type ;

/* Variables and functions */
 int MLX5_ALLOC_TYPE_ALL ; 
 int MLX5_ALLOC_TYPE_CONTIG ; 
 int MLX5_ALLOC_TYPE_HUGE ; 
 int MLX5_ALLOC_TYPE_PREFER_CONTIG ; 
 int MLX5_ALLOC_TYPE_PREFER_HUGE ; 
 int /*<<< orphan*/  MLX5_DBG_CONTIG ; 
 int alloc_huge_buf (struct mlx5_context*,struct mlx5_buf*,size_t,int) ; 
 int mlx5_alloc_buf (struct mlx5_buf*,size_t,int) ; 
 int mlx5_alloc_buf_contig (struct mlx5_context*,struct mlx5_buf*,size_t,int,char const*) ; 
 int /*<<< orphan*/  mlx5_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int mlx5_alloc_prefered_buf(struct mlx5_context *mctx,
			    struct mlx5_buf *buf,
			    size_t size, int page_size,
			    enum mlx5_alloc_type type,
			    const char *component)
{
	int ret;

	/*
	 * Fallback mechanism priority:
	 *	huge pages
	 *	contig pages
	 *	default
	 */
	if (type == MLX5_ALLOC_TYPE_HUGE ||
	    type == MLX5_ALLOC_TYPE_PREFER_HUGE ||
	    type == MLX5_ALLOC_TYPE_ALL) {
		ret = alloc_huge_buf(mctx, buf, size, page_size);
		if (!ret)
			return 0;

		if (type == MLX5_ALLOC_TYPE_HUGE)
			return -1;

		mlx5_dbg(stderr, MLX5_DBG_CONTIG,
			 "Huge mode allocation failed, fallback to %s mode\n",
			 MLX5_ALLOC_TYPE_ALL ? "contig" : "default");
	}

	if (type == MLX5_ALLOC_TYPE_CONTIG ||
	    type == MLX5_ALLOC_TYPE_PREFER_CONTIG ||
	    type == MLX5_ALLOC_TYPE_ALL) {
		ret = mlx5_alloc_buf_contig(mctx, buf, size, page_size, component);
		if (!ret)
			return 0;

		if (type == MLX5_ALLOC_TYPE_CONTIG)
			return -1;
		mlx5_dbg(stderr, MLX5_DBG_CONTIG,
			 "Contig allocation failed, fallback to default mode\n");
	}

	return mlx5_alloc_buf(buf, size, page_size);

}