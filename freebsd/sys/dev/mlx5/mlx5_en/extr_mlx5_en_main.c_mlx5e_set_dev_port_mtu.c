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
struct TYPE_2__ {int hw_mtu; } ;
struct mlx5e_priv {TYPE_1__ params_ethtool; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct ifnet {int if_mtu; struct mlx5e_priv* if_softc; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int MLX5E_HW2SW_MTU (int) ; 
 int MLX5E_SW2HW_MTU (int) ; 
 int /*<<< orphan*/  mlx5_en_err (struct ifnet*,char*,...) ; 
 int mlx5_query_port_oper_mtu (struct mlx5_core_dev*,int*) ; 
 int mlx5_query_vport_mtu (struct mlx5_core_dev*,int*) ; 
 int mlx5_set_port_mtu (struct mlx5_core_dev*,int) ; 
 int mlx5_set_vport_mtu (struct mlx5_core_dev*,int) ; 

__attribute__((used)) static int
mlx5e_set_dev_port_mtu(struct ifnet *ifp, int sw_mtu)
{
	struct mlx5e_priv *priv = ifp->if_softc;
	struct mlx5_core_dev *mdev = priv->mdev;
	int hw_mtu;
	int err;

	hw_mtu = MLX5E_SW2HW_MTU(sw_mtu);

	err = mlx5_set_port_mtu(mdev, hw_mtu);
	if (err) {
		mlx5_en_err(ifp, "mlx5_set_port_mtu failed setting %d, err=%d\n",
		    sw_mtu, err);
		return (err);
	}

	/* Update vport context MTU */
	err = mlx5_set_vport_mtu(mdev, hw_mtu);
	if (err) {
		mlx5_en_err(ifp,
		    "Failed updating vport context with MTU size, err=%d\n",
		    err);
	}

	ifp->if_mtu = sw_mtu;

	err = mlx5_query_vport_mtu(mdev, &hw_mtu);
	if (err || !hw_mtu) {
		/* fallback to port oper mtu */
		err = mlx5_query_port_oper_mtu(mdev, &hw_mtu);
	}
	if (err) {
		mlx5_en_err(ifp,
		    "Query port MTU, after setting new MTU value, failed\n");
		return (err);
	} else if (MLX5E_HW2SW_MTU(hw_mtu) < sw_mtu) {
		err = -E2BIG,
		mlx5_en_err(ifp,
		    "Port MTU %d is smaller than ifp mtu %d\n",
		    hw_mtu, sw_mtu);
	} else if (MLX5E_HW2SW_MTU(hw_mtu) > sw_mtu) {
		err = -EINVAL;
                mlx5_en_err(ifp,
		    "Port MTU %d is bigger than ifp mtu %d\n",
		    hw_mtu, sw_mtu);
	}
	priv->params_ethtool.hw_mtu = hw_mtu;

	return (err);
}