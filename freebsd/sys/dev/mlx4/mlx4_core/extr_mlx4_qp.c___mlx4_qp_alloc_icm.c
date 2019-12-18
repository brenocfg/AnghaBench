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
struct mlx4_qp_table {int /*<<< orphan*/  qp_table; int /*<<< orphan*/  auxc_table; int /*<<< orphan*/  altc_table; int /*<<< orphan*/  rdmarc_table; int /*<<< orphan*/  cmpt_table; } ;
struct mlx4_priv {struct mlx4_qp_table qp_table; } ;
struct mlx4_dev {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_table_get (struct mlx4_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_table_put (struct mlx4_dev*,int /*<<< orphan*/ *,int) ; 

int __mlx4_qp_alloc_icm(struct mlx4_dev *dev, int qpn, gfp_t gfp)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_qp_table *qp_table = &priv->qp_table;
	int err;

	err = mlx4_table_get(dev, &qp_table->qp_table, qpn, gfp);
	if (err)
		goto err_out;

	err = mlx4_table_get(dev, &qp_table->auxc_table, qpn, gfp);
	if (err)
		goto err_put_qp;

	err = mlx4_table_get(dev, &qp_table->altc_table, qpn, gfp);
	if (err)
		goto err_put_auxc;

	err = mlx4_table_get(dev, &qp_table->rdmarc_table, qpn, gfp);
	if (err)
		goto err_put_altc;

	err = mlx4_table_get(dev, &qp_table->cmpt_table, qpn, gfp);
	if (err)
		goto err_put_rdmarc;

	return 0;

err_put_rdmarc:
	mlx4_table_put(dev, &qp_table->rdmarc_table, qpn);

err_put_altc:
	mlx4_table_put(dev, &qp_table->altc_table, qpn);

err_put_auxc:
	mlx4_table_put(dev, &qp_table->auxc_table, qpn);

err_put_qp:
	mlx4_table_put(dev, &qp_table->qp_table, qpn);

err_out:
	return err;
}