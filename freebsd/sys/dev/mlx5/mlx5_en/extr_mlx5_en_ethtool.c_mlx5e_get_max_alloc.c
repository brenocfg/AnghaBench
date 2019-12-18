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
struct TYPE_2__ {int* max_bw_share; } ;
struct mlx5e_priv {TYPE_1__ params_ethtool; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int IEEE_8021QAZ_MAX_TCS ; 
 int /*<<< orphan*/  PRIV_LOCK (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  PRIV_UNLOCK (struct mlx5e_priv*) ; 
 int mlx5_query_port_tc_bw_alloc (struct mlx5_core_dev*,int*) ; 
 int mlx5_set_port_tc_bw_alloc (struct mlx5_core_dev*,int*) ; 

__attribute__((used)) static int
mlx5e_get_max_alloc(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	int err;
	int x;

	PRIV_LOCK(priv);
	err = -mlx5_query_port_tc_bw_alloc(mdev, priv->params_ethtool.max_bw_share);
	if (err == 0) {
		/* set default value */
		for (x = 0; x != IEEE_8021QAZ_MAX_TCS; x++) {
			priv->params_ethtool.max_bw_share[x] =
			    100 / IEEE_8021QAZ_MAX_TCS;
		}
		err = -mlx5_set_port_tc_bw_alloc(mdev,
		    priv->params_ethtool.max_bw_share);
	}
	PRIV_UNLOCK(priv);

	return (err);
}