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
typedef  void u32 ;
struct mlx5_srq_attr {int /*<<< orphan*/  flags; } ;
struct mlx5_core_srq {int /*<<< orphan*/  srqn; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_ADDR_OF (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_GET (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_RMPC_STATE_RDY ; 
 int /*<<< orphan*/  MLX5_SRQ_FLAG_ERR ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (void*) ; 
 int /*<<< orphan*/  get_wq (void*,struct mlx5_srq_attr*) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int mlx5_core_query_rmp (struct mlx5_core_dev*,int /*<<< orphan*/ ,void*) ; 
 void* mlx5_vzalloc (int /*<<< orphan*/ ) ; 
 void* query_rmp_out ; 
 int /*<<< orphan*/  rmp_context ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static int query_rmp_cmd(struct mlx5_core_dev *dev, struct mlx5_core_srq *srq,
			 struct mlx5_srq_attr *out)
{
	u32 *rmp_out;
	void *rmpc;
	int err;

	rmp_out =  mlx5_vzalloc(MLX5_ST_SZ_BYTES(query_rmp_out));
	if (!rmp_out)
		return -ENOMEM;

	err = mlx5_core_query_rmp(dev, srq->srqn, rmp_out);
	if (err)
		goto out;

	rmpc = MLX5_ADDR_OF(query_rmp_out, rmp_out, rmp_context);
	get_wq(MLX5_ADDR_OF(rmpc, rmpc, wq), out);
	if (MLX5_GET(rmpc, rmpc, state) != MLX5_RMPC_STATE_RDY)
		out->flags |= MLX5_SRQ_FLAG_ERR;

out:
	kvfree(rmp_out);
	return 0;
}