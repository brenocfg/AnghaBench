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
struct mlx5e_priv {int dummy; } ;
struct mlx5e_cq_param {int dummy; } ;
struct mlx5e_cq {int dummy; } ;
typedef  int /*<<< orphan*/  mlx5e_cq_comp_t ;

/* Variables and functions */
 int mlx5e_create_cq (struct mlx5e_priv*,struct mlx5e_cq_param*,struct mlx5e_cq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5e_destroy_cq (struct mlx5e_cq*) ; 
 int mlx5e_enable_cq (struct mlx5e_cq*,struct mlx5e_cq_param*,int) ; 

int
mlx5e_open_cq(struct mlx5e_priv *priv,
    struct mlx5e_cq_param *param,
    struct mlx5e_cq *cq,
    mlx5e_cq_comp_t *comp,
    int eq_ix)
{
	int err;

	err = mlx5e_create_cq(priv, param, cq, comp, eq_ix);
	if (err)
		return (err);

	err = mlx5e_enable_cq(cq, param, eq_ix);
	if (err)
		goto err_destroy_cq;

	return (0);

err_destroy_cq:
	mlx5e_destroy_cq(cq);

	return (err);
}