#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_priv {TYPE_1__* ifp; int /*<<< orphan*/  mdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MLX5_PORT_UP ; 
 int /*<<< orphan*/  PRIV_LOCK (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  PRIV_UNLOCK (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5_en_err (TYPE_1__*,char*) ; 
 scalar_t__ mlx5_set_port_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_open_locked (TYPE_1__*) ; 

__attribute__((used)) static void
mlx5e_open(void *arg)
{
	struct mlx5e_priv *priv = arg;

	PRIV_LOCK(priv);
	if (mlx5_set_port_status(priv->mdev, MLX5_PORT_UP))
		mlx5_en_err(priv->ifp,
		    "Setting port status to up failed\n");

	mlx5e_open_locked(priv->ifp);
	priv->ifp->if_drv_flags |= IFF_DRV_RUNNING;
	PRIV_UNLOCK(priv);
}