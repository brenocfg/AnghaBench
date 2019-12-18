#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mlx4_en_priv {int flags; int /*<<< orphan*/  port; int /*<<< orphan*/  base_qpn; } ;
struct mlx4_en_dev {TYPE_2__* dev; } ;
struct TYPE_7__ {int steering_mode; } ;
struct TYPE_8__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int MLX4_EN_FLAG_MC_PROMISC ; 
 int MLX4_EN_FLAG_PROMISC ; 
 int /*<<< orphan*/  MLX4_FS_ALL_DEFAULT ; 
 int /*<<< orphan*/  MLX4_MCAST_DISABLE ; 
#define  MLX4_STEERING_MODE_A0 130 
#define  MLX4_STEERING_MODE_B0 129 
#define  MLX4_STEERING_MODE_DEVICE_MANAGED 128 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int mlx4_SET_MCAST_FLTR (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_SET_PORT_qpn_calc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlx4_flow_steer_promisc_add (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_multicast_promisc_add (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_unicast_promisc_add (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_en_set_promisc_mode(struct mlx4_en_priv *priv,
				     struct mlx4_en_dev *mdev)
{
	int err = 0;

	if (!(priv->flags & MLX4_EN_FLAG_PROMISC)) {
		priv->flags |= MLX4_EN_FLAG_PROMISC;

		/* Enable promiscouos mode */
		switch (mdev->dev->caps.steering_mode) {
		case MLX4_STEERING_MODE_DEVICE_MANAGED:
			err = mlx4_flow_steer_promisc_add(mdev->dev,
							  priv->port,
							  priv->base_qpn,
							  MLX4_FS_ALL_DEFAULT);
			if (err)
				en_err(priv, "Failed enabling promiscuous mode\n");
			priv->flags |= MLX4_EN_FLAG_MC_PROMISC;
			break;

		case MLX4_STEERING_MODE_B0:
			err = mlx4_unicast_promisc_add(mdev->dev,
						       priv->base_qpn,
						       priv->port);
			if (err)
				en_err(priv, "Failed enabling unicast promiscuous mode\n");

			/* Add the default qp number as multicast
			 * promisc
			 */
			if (!(priv->flags & MLX4_EN_FLAG_MC_PROMISC)) {
				err = mlx4_multicast_promisc_add(mdev->dev,
								 priv->base_qpn,
								 priv->port);
				if (err)
					en_err(priv, "Failed enabling multicast promiscuous mode\n");
				priv->flags |= MLX4_EN_FLAG_MC_PROMISC;
			}
			break;

		case MLX4_STEERING_MODE_A0:
			err = mlx4_SET_PORT_qpn_calc(mdev->dev,
						     priv->port,
						     priv->base_qpn,
						     1);
			if (err)
				en_err(priv, "Failed enabling promiscuous mode\n");
			break;
		}

		/* Disable port multicast filter (unconditionally) */
		err = mlx4_SET_MCAST_FLTR(mdev->dev, priv->port, 0,
					  0, MLX4_MCAST_DISABLE);
		if (err)
			en_err(priv, "Failed disabling multicast filter\n");
	}
}