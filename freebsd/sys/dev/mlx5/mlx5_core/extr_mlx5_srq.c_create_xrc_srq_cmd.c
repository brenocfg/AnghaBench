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
struct mlx5_srq_attr {int /*<<< orphan*/  pas; int /*<<< orphan*/  user_index; } ;
struct mlx5_core_srq {int /*<<< orphan*/  srqn; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_xrc_srq_in ; 
 int get_pas_size (struct mlx5_srq_attr*) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int mlx5_core_create_xsrq (struct mlx5_core_dev*,void*,int,int /*<<< orphan*/ *) ; 
 void* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  set_srqc (void*,struct mlx5_srq_attr*) ; 
 int /*<<< orphan*/  user_index ; 
 void* xrc_srq_context_entry ; 

__attribute__((used)) static int create_xrc_srq_cmd(struct mlx5_core_dev *dev,
			      struct mlx5_core_srq *srq,
			      struct mlx5_srq_attr *in)
{
	void *create_in;
	void *xrc_srqc;
	void *pas;
	int pas_size;
	int inlen;
	int err;

	pas_size  = get_pas_size(in);
	inlen	  = MLX5_ST_SZ_BYTES(create_xrc_srq_in) + pas_size;
	create_in = mlx5_vzalloc(inlen);
	if (!create_in)
		return -ENOMEM;

	xrc_srqc = MLX5_ADDR_OF(create_xrc_srq_in, create_in, xrc_srq_context_entry);
	pas	 = MLX5_ADDR_OF(create_xrc_srq_in, create_in, pas);

	set_srqc(xrc_srqc, in);
	MLX5_SET(xrc_srqc, xrc_srqc, user_index, in->user_index);
	memcpy(pas, in->pas, pas_size);

	err = mlx5_core_create_xsrq(dev, create_in, inlen, &srq->srqn);
	if (err)
		goto out;

out:
	kvfree(create_in);
	return err;
}