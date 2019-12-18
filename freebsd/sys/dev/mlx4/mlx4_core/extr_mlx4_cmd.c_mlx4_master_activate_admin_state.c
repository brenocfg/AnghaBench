#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct mlx4_vport_state {scalar_t__ vlan_proto; scalar_t__ default_vlan; scalar_t__ mac; scalar_t__ spoofchk; int /*<<< orphan*/  guid; int /*<<< orphan*/  qos_vport; int /*<<< orphan*/  tx_rate; int /*<<< orphan*/  default_qos; } ;
struct TYPE_17__ {scalar_t__ vlan_proto; scalar_t__ default_vlan; scalar_t__ mac; int /*<<< orphan*/  guid; int /*<<< orphan*/  qos_vport; int /*<<< orphan*/  tx_rate; scalar_t__ spoofchk; int /*<<< orphan*/  default_qos; } ;
struct mlx4_vport_oper_state {int vlan_idx; int mac_idx; TYPE_6__ state; } ;
struct mlx4_slave_state {scalar_t__ vst_qinq_supported; } ;
struct TYPE_12__ {int /*<<< orphan*/  num_ports; } ;
struct TYPE_18__ {TYPE_1__ caps; } ;
struct TYPE_15__ {TYPE_3__* vf_admin; TYPE_2__* vf_oper; struct mlx4_slave_state* slave_state; } ;
struct TYPE_16__ {TYPE_4__ master; } ;
struct mlx4_priv {TYPE_7__ dev; TYPE_5__ mfunc; } ;
struct mlx4_active_ports {int /*<<< orphan*/  ports; } ;
struct TYPE_14__ {struct mlx4_vport_state* vport; int /*<<< orphan*/ * enable_smi; } ;
struct TYPE_13__ {struct mlx4_vport_oper_state* vport; int /*<<< orphan*/ * smi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021AD ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ MLX4_VGT ; 
 void* NO_INDX ; 
 int __mlx4_register_mac (TYPE_7__*,int,scalar_t__) ; 
 int __mlx4_register_vlan (TYPE_7__*,int,scalar_t__,int*) ; 
 int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int find_first_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_dbg (TYPE_7__*,char*,unsigned long long,int,int,int) ; 
 struct mlx4_active_ports mlx4_get_active_ports (TYPE_7__*,int) ; 
 int /*<<< orphan*/  mlx4_warn (TYPE_7__*,char*,int,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_master_activate_admin_state(struct mlx4_priv *priv, int slave)
{
	int port, err;
	struct mlx4_vport_state *vp_admin;
	struct mlx4_vport_oper_state *vp_oper;
	struct mlx4_slave_state *slave_state =
		&priv->mfunc.master.slave_state[slave];
	struct mlx4_active_ports actv_ports = mlx4_get_active_ports(
			&priv->dev, slave);
	int min_port = find_first_bit(actv_ports.ports,
				      priv->dev.caps.num_ports) + 1;
	int max_port = min_port - 1 +
		bitmap_weight(actv_ports.ports, priv->dev.caps.num_ports);

	for (port = min_port; port <= max_port; port++) {
		if (!test_bit(port - 1, actv_ports.ports))
			continue;
		priv->mfunc.master.vf_oper[slave].smi_enabled[port] =
			priv->mfunc.master.vf_admin[slave].enable_smi[port];
		vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
		vp_admin = &priv->mfunc.master.vf_admin[slave].vport[port];
		if (vp_admin->vlan_proto != htons(ETH_P_8021AD) ||
		    slave_state->vst_qinq_supported) {
			vp_oper->state.vlan_proto   = vp_admin->vlan_proto;
			vp_oper->state.default_vlan = vp_admin->default_vlan;
			vp_oper->state.default_qos  = vp_admin->default_qos;
		}
		vp_oper->state.mac        = vp_admin->mac;
		vp_oper->state.spoofchk   = vp_admin->spoofchk;
		vp_oper->state.tx_rate    = vp_admin->tx_rate;
		vp_oper->state.qos_vport  = vp_admin->qos_vport;
		vp_oper->state.guid       = vp_admin->guid;

		if (MLX4_VGT != vp_admin->default_vlan) {
			err = __mlx4_register_vlan(&priv->dev, port,
						   vp_admin->default_vlan, &(vp_oper->vlan_idx));
			if (err) {
				vp_oper->vlan_idx = NO_INDX;
				vp_oper->state.default_vlan = MLX4_VGT;
				vp_oper->state.vlan_proto = htons(ETH_P_8021Q);
				mlx4_warn(&priv->dev,
					  "No vlan resources slave %d, port %d\n",
					  slave, port);
				return err;
			}
			mlx4_dbg(&priv->dev, "alloc vlan %d idx  %d slave %d port %d\n",
				 (int)(vp_oper->state.default_vlan),
				 vp_oper->vlan_idx, slave, port);
		}
		if (vp_admin->spoofchk) {
			vp_oper->mac_idx = __mlx4_register_mac(&priv->dev,
							       port,
							       vp_admin->mac);
			if (0 > vp_oper->mac_idx) {
				err = vp_oper->mac_idx;
				vp_oper->mac_idx = NO_INDX;
				mlx4_warn(&priv->dev,
					  "No mac resources slave %d, port %d\n",
					  slave, port);
				return err;
			}
			mlx4_dbg(&priv->dev, "alloc mac %llx idx  %d slave %d port %d\n",
				 (unsigned long long) vp_oper->state.mac, vp_oper->mac_idx, slave, port);
		}
	}
	return 0;
}