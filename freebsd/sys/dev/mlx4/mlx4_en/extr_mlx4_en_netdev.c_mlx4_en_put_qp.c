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
struct mlx4_en_priv {int base_qpn; int /*<<< orphan*/  flags; int /*<<< orphan*/  port; int /*<<< orphan*/  dev; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {struct mlx4_dev* dev; } ;
struct TYPE_2__ {scalar_t__ steering_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int /*<<< orphan*/  IF_LLADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX4_EN_FLAG_FORCE_PROMISC ; 
 scalar_t__ MLX4_STEERING_MODE_A0 ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlx4_mac_to_u64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_qp_release_range (struct mlx4_dev*,int,int) ; 
 int /*<<< orphan*/  mlx4_unregister_mac (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_en_put_qp(struct mlx4_en_priv *priv)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_dev *dev = mdev->dev;
	int qpn = priv->base_qpn;

	if (dev->caps.steering_mode == MLX4_STEERING_MODE_A0) {
		u64 mac = mlx4_mac_to_u64(IF_LLADDR(priv->dev));
		en_dbg(DRV, priv, "Registering MAC: %pM for deleting\n",
		       IF_LLADDR(priv->dev));
		mlx4_unregister_mac(dev, priv->port, mac);
	} else {
		en_dbg(DRV, priv, "Releasing qp: port %d, qpn %d\n",
		       priv->port, qpn);
		mlx4_qp_release_range(dev, qpn, 1);
		priv->flags &= ~MLX4_EN_FLAG_FORCE_PROMISC;
	}
}