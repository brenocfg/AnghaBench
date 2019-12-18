#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx4_vport_state {int spoofchk; } ;
struct TYPE_6__ {TYPE_1__* vf_admin; } ;
struct TYPE_7__ {TYPE_2__ master; } ;
struct mlx4_priv {TYPE_3__ mfunc; } ;
struct TYPE_8__ {int flags2; } ;
struct mlx4_dev {TYPE_4__ caps; } ;
struct TYPE_5__ {struct mlx4_vport_state* vport; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int MLX4_DEV_CAP_FLAG2_FSM ; 
 int mlx4_get_slave_indx (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_is_master (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_slaves_closest_port (struct mlx4_dev*,int,int) ; 

int mlx4_set_vf_spoofchk(struct mlx4_dev *dev, int port, int vf, bool setting)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_vport_state *s_info;
	int slave;

	if ((!mlx4_is_master(dev)) ||
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_FSM))
		return -EPROTONOSUPPORT;

	slave = mlx4_get_slave_indx(dev, vf);
	if (slave < 0)
		return -EINVAL;

	port = mlx4_slaves_closest_port(dev, slave, port);
	s_info = &priv->mfunc.master.vf_admin[slave].vport[port];
	s_info->spoofchk = setting;

	return 0;
}