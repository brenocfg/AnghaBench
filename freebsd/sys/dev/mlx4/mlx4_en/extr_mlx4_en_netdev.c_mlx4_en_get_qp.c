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
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_en_priv {int base_qpn; int /*<<< orphan*/  port; int /*<<< orphan*/  dev; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {struct mlx4_dev* dev; } ;
struct TYPE_2__ {scalar_t__ steering_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int IF_LLADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX4_RESERVE_A0_QP ; 
 scalar_t__ MLX4_STEERING_MODE_A0 ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,...) ; 
 int mlx4_get_base_qpn (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_mac_to_u64 (int) ; 
 int mlx4_qp_reserve_range (struct mlx4_dev*,int,int,int*,int /*<<< orphan*/ ) ; 
 int mlx4_register_mac (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_unregister_mac (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_en_get_qp(struct mlx4_en_priv *priv)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_dev *dev = mdev->dev;
	int index = 0;
	int err = 0;
	int *qpn = &priv->base_qpn;
	u64 mac = mlx4_mac_to_u64(IF_LLADDR(priv->dev));

	en_dbg(DRV, priv, "Registering MAC: %pM for adding\n",
	       IF_LLADDR(priv->dev));
	index = mlx4_register_mac(dev, priv->port, mac);
	if (index < 0) {
		err = index;
		en_err(priv, "Failed adding MAC: %pM\n",
		       IF_LLADDR(priv->dev));
		return err;
	}

	if (dev->caps.steering_mode == MLX4_STEERING_MODE_A0) {
		int base_qpn = mlx4_get_base_qpn(dev, priv->port);
		*qpn = base_qpn + index;
		return 0;
	}

	err = mlx4_qp_reserve_range(dev, 1, 1, qpn, MLX4_RESERVE_A0_QP);
	en_dbg(DRV, priv, "Reserved qp %d\n", *qpn);
	if (err) {
		en_err(priv, "Failed to reserve qp for mac registration\n");
		mlx4_unregister_mac(dev, priv->port, mac);
		return err;
	}

	return 0;
}