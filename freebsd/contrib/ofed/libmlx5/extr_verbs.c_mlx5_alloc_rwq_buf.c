#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int wqe_cnt; int /*<<< orphan*/  wrid; } ;
struct mlx5_rwq {TYPE_1__ rq; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf; } ;
struct ibv_context {int /*<<< orphan*/  device; } ;
typedef  enum mlx5_alloc_type { ____Placeholder_mlx5_alloc_type } mlx5_alloc_type ;
struct TYPE_4__ {int /*<<< orphan*/  page_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int MLX5_ALLOC_TYPE_PREFER_CONTIG ; 
 int /*<<< orphan*/  MLX5_RWQ_PREFIX ; 
 int /*<<< orphan*/  align (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int mlx5_alloc_prefered_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mctx (struct ibv_context*) ; 
 TYPE_2__* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_alloc_rwq_buf(struct ibv_context *context,
			      struct mlx5_rwq *rwq,
			      int size)
{
	int err;
	enum mlx5_alloc_type default_alloc_type = MLX5_ALLOC_TYPE_PREFER_CONTIG;

	rwq->rq.wrid = malloc(rwq->rq.wqe_cnt * sizeof(uint64_t));
	if (!rwq->rq.wrid) {
		errno = ENOMEM;
		return -1;
	}

	err = mlx5_alloc_prefered_buf(to_mctx(context), &rwq->buf,
				      align(rwq->buf_size, to_mdev
				      (context->device)->page_size),
				      to_mdev(context->device)->page_size,
				      default_alloc_type,
				      MLX5_RWQ_PREFIX);

	if (err) {
		free(rwq->rq.wrid);
		errno = ENOMEM;
		return -1;
	}

	return 0;
}