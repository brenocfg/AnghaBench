#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_rq_param {int dummy; } ;
struct mlx5e_rq {int dummy; } ;
struct TYPE_2__ {int enabled; } ;
struct mlx5e_channel {TYPE_1__ rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_RQC_STATE_RDY ; 
 int /*<<< orphan*/  MLX5_RQC_STATE_RST ; 
 int mlx5e_create_rq (struct mlx5e_channel*,struct mlx5e_rq_param*,struct mlx5e_rq*) ; 
 int /*<<< orphan*/  mlx5e_destroy_rq (struct mlx5e_rq*) ; 
 int /*<<< orphan*/  mlx5e_disable_rq (struct mlx5e_rq*) ; 
 int mlx5e_enable_rq (struct mlx5e_rq*,struct mlx5e_rq_param*) ; 
 int mlx5e_modify_rq (struct mlx5e_rq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlx5e_open_rq(struct mlx5e_channel *c,
    struct mlx5e_rq_param *param,
    struct mlx5e_rq *rq)
{
	int err;

	err = mlx5e_create_rq(c, param, rq);
	if (err)
		return (err);

	err = mlx5e_enable_rq(rq, param);
	if (err)
		goto err_destroy_rq;

	err = mlx5e_modify_rq(rq, MLX5_RQC_STATE_RST, MLX5_RQC_STATE_RDY);
	if (err)
		goto err_disable_rq;

	c->rq.enabled = 1;

	return (0);

err_disable_rq:
	mlx5e_disable_rq(rq);
err_destroy_rq:
	mlx5e_destroy_rq(rq);

	return (err);
}