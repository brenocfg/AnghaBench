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
struct TYPE_2__ {int /*<<< orphan*/  trust_state; int /*<<< orphan*/  dscp2prio; } ;
struct mlx5e_priv {TYPE_1__ params_ethtool; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_QCAM_REG (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIV_LOCK (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  PRIV_UNLOCK (struct mlx5e_priv*) ; 
 int mlx5_query_dscp2prio (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_query_trust_state (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcam_reg ; 
 int /*<<< orphan*/  qpdpm ; 
 int /*<<< orphan*/  qpts ; 

__attribute__((used)) static int
mlx5e_get_dscp(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	int err;

	if (MLX5_CAP_GEN(mdev, qcam_reg) == 0 ||
	    MLX5_CAP_QCAM_REG(mdev, qpts) == 0 ||
	    MLX5_CAP_QCAM_REG(mdev, qpdpm) == 0)
		return (EOPNOTSUPP);

	PRIV_LOCK(priv);
	err = -mlx5_query_dscp2prio(mdev, priv->params_ethtool.dscp2prio);
	if (err)
		goto done;

	err = -mlx5_query_trust_state(mdev, &priv->params_ethtool.trust_state);
	if (err)
		goto done;
done:
	PRIV_UNLOCK(priv);
	return (err);
}