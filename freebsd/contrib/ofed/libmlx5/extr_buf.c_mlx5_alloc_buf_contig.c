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
struct ibv_context {int /*<<< orphan*/  cmd_fd; } ;
struct mlx5_context {int /*<<< orphan*/  dbg_fp; struct ibv_context ibv_ctx; } ;
struct mlx5_buf {size_t length; int /*<<< orphan*/  type; void* buf; } ;
typedef  int off_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  MLX5_ALLOC_TYPE_CONTIG ; 
 int /*<<< orphan*/  MLX5_DBG_CONTIG ; 
 int /*<<< orphan*/  MLX5_MMAP_GET_CONTIGUOUS_PAGES_CMD ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ errno ; 
 scalar_t__ ibv_dontfork_range (void*,size_t) ; 
 int /*<<< orphan*/  mlx5_alloc_get_env_info (int*,int*,char const*) ; 
 int /*<<< orphan*/  mlx5_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,void*) ; 
 int mlx5_get_block_order (size_t) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 
 int /*<<< orphan*/  set_command (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set_order (int,int*) ; 

int mlx5_alloc_buf_contig(struct mlx5_context *mctx,
			  struct mlx5_buf *buf, size_t size,
			  int page_size,
			  const char *component)
{
	void *addr = MAP_FAILED;
	int block_size_exp;
	int max_block_log;
	int min_block_log;
	struct ibv_context *context = &mctx->ibv_ctx;
	off_t offset;

	mlx5_alloc_get_env_info(&max_block_log,
				&min_block_log,
				component);

	block_size_exp = mlx5_get_block_order(size);

	if (block_size_exp > max_block_log)
		block_size_exp = max_block_log;

	do {
		offset = 0;
		set_command(MLX5_MMAP_GET_CONTIGUOUS_PAGES_CMD, &offset);
		set_order(block_size_exp, &offset);
		addr = mmap(NULL , size, PROT_WRITE | PROT_READ, MAP_SHARED,
			    context->cmd_fd, page_size * offset);
		if (addr != MAP_FAILED)
			break;

		/*
		 *  The kernel returns EINVAL if not supported
		 */
		if (errno == EINVAL)
			return -1;

		block_size_exp -= 1;
	} while (block_size_exp >= min_block_log);
	mlx5_dbg(mctx->dbg_fp, MLX5_DBG_CONTIG, "block order %d, addr %p\n",
		 block_size_exp, addr);

	if (addr == MAP_FAILED)
		return -1;

	if (ibv_dontfork_range(addr, size)) {
		munmap(addr, size);
		return -1;
	}

	buf->buf = addr;
	buf->length = size;
	buf->type = MLX5_ALLOC_TYPE_CONTIG;

	return 0;
}