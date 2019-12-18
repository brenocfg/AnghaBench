#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* vf_admin; } ;
struct TYPE_6__ {TYPE_2__ master; } ;
struct mlx4_priv {TYPE_3__ mfunc; } ;
struct mlx4_dev {int num_slaves; } ;
struct TYPE_4__ {scalar_t__* enable_smi; } ;

/* Variables and functions */
 int MLX4_MAX_PORTS ; 
 scalar_t__ MLX4_VF_SMI_ENABLED ; 
 int mlx4_master_func_num (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_vf_get_enable_smi_admin(struct mlx4_dev *dev, int slave, int port)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	if (slave == mlx4_master_func_num(dev))
		return 1;

	if (slave < 1 || slave >= dev->num_slaves ||
	    port < 1 || port > MLX4_MAX_PORTS)
		return 0;

	return priv->mfunc.master.vf_admin[slave].enable_smi[port] ==
		MLX4_VF_SMI_ENABLED;
}