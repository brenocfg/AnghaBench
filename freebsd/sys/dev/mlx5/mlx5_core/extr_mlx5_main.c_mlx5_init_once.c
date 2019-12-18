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
struct mlx5_priv {int /*<<< orphan*/  cq_uar_lock; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_INIT_DOORBELL_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_cleanup_cq_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_mr_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_qp_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_srq_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_eq_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_eq_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fpga_init (struct mlx5_core_dev*) ; 
 int mlx5_init_cq_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_mr_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_qp_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_reserved_gids (struct mlx5_core_dev*) ; 
 int mlx5_init_rl_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_init_srq_table (struct mlx5_core_dev*) ; 
 int mlx5_query_board_id (struct mlx5_core_dev*) ; 
 int mlx5_query_hca_caps (struct mlx5_core_dev*) ; 
 int mlx5_vsc_find_cap (struct mlx5_core_dev*) ; 

__attribute__((used)) static int mlx5_init_once(struct mlx5_core_dev *dev, struct mlx5_priv *priv)
{
	int err;

	err = mlx5_vsc_find_cap(dev);
	if (err)
		mlx5_core_err(dev, "Unable to find vendor specific capabilities\n");

	err = mlx5_query_hca_caps(dev);
	if (err) {
		mlx5_core_err(dev, "query hca failed\n");
		goto out;
	}

	err = mlx5_query_board_id(dev);
	if (err) {
		mlx5_core_err(dev, "query board id failed\n");
		goto out;
	}

	err = mlx5_eq_init(dev);
	if (err) {
		mlx5_core_err(dev, "failed to initialize eq\n");
		goto out;
	}

	MLX5_INIT_DOORBELL_LOCK(&priv->cq_uar_lock);

	err = mlx5_init_cq_table(dev);
	if (err) {
		mlx5_core_err(dev, "failed to initialize cq table\n");
		goto err_eq_cleanup;
	}

	mlx5_init_qp_table(dev);
	mlx5_init_srq_table(dev);
	mlx5_init_mr_table(dev);

	mlx5_init_reserved_gids(dev);
	mlx5_fpga_init(dev);

#ifdef RATELIMIT
	err = mlx5_init_rl_table(dev);
	if (err) {
		mlx5_core_err(dev, "Failed to init rate limiting\n");
		goto err_tables_cleanup;
	}
#endif
	return 0;

#ifdef RATELIMIT
err_tables_cleanup:
	mlx5_cleanup_mr_table(dev);
	mlx5_cleanup_srq_table(dev);
	mlx5_cleanup_qp_table(dev);
	mlx5_cleanup_cq_table(dev);
#endif

err_eq_cleanup:
	mlx5_eq_cleanup(dev);

out:
	return err;
}