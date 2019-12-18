#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct mlx4_vport_state {int default_vlan; int default_qos; int qos_vport; scalar_t__ tx_rate; scalar_t__ vlan_proto; } ;
struct TYPE_12__ {scalar_t__ vlan_proto; } ;
struct mlx4_vport_oper_state {TYPE_6__ state; } ;
struct mlx4_slave_state {int /*<<< orphan*/  vst_qinq_supported; scalar_t__ active; } ;
struct TYPE_10__ {TYPE_3__* vf_oper; TYPE_2__* vf_admin; struct mlx4_slave_state* slave_state; } ;
struct TYPE_11__ {TYPE_4__ master; } ;
struct mlx4_priv {TYPE_5__ mfunc; } ;
struct TYPE_7__ {int flags2; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_9__ {struct mlx4_vport_oper_state* vport; } ;
struct TYPE_8__ {struct mlx4_vport_state* vport; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021AD ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int MLX4_DEV_CAP_FLAG2_SVLAN_BY_QP ; 
 int MLX4_DEV_CAP_FLAG2_VLAN_CONTROL ; 
 int MLX4_VGT ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,int) ; 
 int mlx4_get_slave_indx (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_info (struct mlx4_dev*,char*,int,int) ; 
 int /*<<< orphan*/  mlx4_is_master (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_vf_vst_and_prio_qos (struct mlx4_dev*,int,struct mlx4_vport_state*) ; 
 scalar_t__ mlx4_master_immediate_activate_vlan_qos (struct mlx4_priv*,int,int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_slaves_closest_port (struct mlx4_dev*,int,int) ; 
 int /*<<< orphan*/  mlx4_valid_vf_state_change (struct mlx4_dev*,int,struct mlx4_vport_state*,int,int) ; 

int mlx4_set_vf_vlan(struct mlx4_dev *dev, int port, int vf, u16 vlan, u8 qos,
		     __be16 proto)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_vport_state *vf_admin;
	struct mlx4_slave_state *slave_state;
	struct mlx4_vport_oper_state *vf_oper;
	int slave;

	if ((!mlx4_is_master(dev)) ||
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_VLAN_CONTROL))
		return -EPROTONOSUPPORT;

	if ((vlan > 4095) || (qos > 7))
		return -EINVAL;

	if (proto == htons(ETH_P_8021AD) &&
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SVLAN_BY_QP))
		return -EPROTONOSUPPORT;

	if (proto != htons(ETH_P_8021Q) &&
	    proto != htons(ETH_P_8021AD))
		return -EINVAL;

	if ((proto == htons(ETH_P_8021AD)) &&
	    ((vlan == 0) || (vlan == MLX4_VGT)))
		return -EINVAL;

	slave = mlx4_get_slave_indx(dev, vf);
	if (slave < 0)
		return -EINVAL;

	slave_state = &priv->mfunc.master.slave_state[slave];
	if ((proto == htons(ETH_P_8021AD)) && (slave_state->active) &&
	    (!slave_state->vst_qinq_supported)) {
		mlx4_err(dev, "vf %d does not support VST QinQ mode\n", vf);
		return -EPROTONOSUPPORT;
	}
	port = mlx4_slaves_closest_port(dev, slave, port);
	vf_admin = &priv->mfunc.master.vf_admin[slave].vport[port];
	vf_oper = &priv->mfunc.master.vf_oper[slave].vport[port];

	if (!mlx4_valid_vf_state_change(dev, port, vf_admin, vlan, qos))
		return -EPERM;

	if ((0 == vlan) && (0 == qos))
		vf_admin->default_vlan = MLX4_VGT;
	else
		vf_admin->default_vlan = vlan;
	vf_admin->default_qos = qos;
	vf_admin->vlan_proto = proto;

	/* If rate was configured prior to VST, we saved the configured rate
	 * in vf_admin->rate and now, if priority supported we enforce the QoS
	 */
	if (mlx4_is_vf_vst_and_prio_qos(dev, port, vf_admin) &&
	    vf_admin->tx_rate)
		vf_admin->qos_vport = slave;

	/* Try to activate new vf state without restart,
	 * this option is not supported while moving to VST QinQ mode.
	 */
	if ((proto == htons(ETH_P_8021AD) &&
	     vf_oper->state.vlan_proto != proto) ||
	    mlx4_master_immediate_activate_vlan_qos(priv, slave, port))
		mlx4_info(dev,
			  "updating vf %d port %d config will take effect on next VF restart\n",
			  vf, port);
	return 0;
}