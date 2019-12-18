#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_slaves_pport {int /*<<< orphan*/  slaves; } ;
struct mlx4_priv {TYPE_3__* port; } ;
struct TYPE_9__ {int num_ports; } ;
struct mlx4_dev {TYPE_5__* persist; TYPE_4__ caps; } ;
struct mlx4_active_ports {int /*<<< orphan*/  ports; } ;
struct TYPE_10__ {int num_vfs; } ;
struct TYPE_7__ {TYPE_1__* roce_gids; } ;
struct TYPE_8__ {TYPE_2__ gid_table; } ;
struct TYPE_6__ {int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX4_ROCE_GID_ENTRY_SIZE ; 
 int MLX4_ROCE_MAX_GIDS ; 
 int MLX4_ROCE_PF_GIDS ; 
 int bitmap_weight (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx4_active_ports mlx4_get_active_ports (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_is_mfunc (struct mlx4_dev*) ; 
 struct mlx4_slaves_pport mlx4_phys_to_slaves_pport (struct mlx4_dev*,int) ; 
 struct mlx4_slaves_pport mlx4_phys_to_slaves_pport_actv (struct mlx4_dev*,struct mlx4_active_ports*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

int mlx4_get_slave_from_roce_gid(struct mlx4_dev *dev, int port, u8 *gid,
				 int *slave_id)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int i, found_ix = -1;
	int vf_gids = MLX4_ROCE_MAX_GIDS - MLX4_ROCE_PF_GIDS;
	struct mlx4_slaves_pport slaves_pport;
	unsigned num_vfs;
	int slave_gid;

	if (!mlx4_is_mfunc(dev))
		return -EINVAL;

	slaves_pport = mlx4_phys_to_slaves_pport(dev, port);
	num_vfs = bitmap_weight(slaves_pport.slaves,
				dev->persist->num_vfs + 1) - 1;

	for (i = 0; i < MLX4_ROCE_MAX_GIDS; i++) {
		if (!memcmp(priv->port[port].gid_table.roce_gids[i].raw, gid,
			    MLX4_ROCE_GID_ENTRY_SIZE)) {
			found_ix = i;
			break;
		}
	}

	if (found_ix >= 0) {
		/* Calculate a slave_gid which is the slave number in the gid
		 * table and not a globally unique slave number.
		 */
		if (found_ix < MLX4_ROCE_PF_GIDS)
			slave_gid = 0;
		else if (found_ix < MLX4_ROCE_PF_GIDS + (vf_gids % num_vfs) *
			 (vf_gids / num_vfs + 1))
			slave_gid = ((found_ix - MLX4_ROCE_PF_GIDS) /
				     (vf_gids / num_vfs + 1)) + 1;
		else
			slave_gid =
			((found_ix - MLX4_ROCE_PF_GIDS -
			  ((vf_gids % num_vfs) * ((vf_gids / num_vfs + 1)))) /
			 (vf_gids / num_vfs)) + vf_gids % num_vfs + 1;

		/* Calculate the globally unique slave id */
		if (slave_gid) {
			struct mlx4_active_ports exclusive_ports;
			struct mlx4_active_ports actv_ports;
			struct mlx4_slaves_pport slaves_pport_actv;
			unsigned max_port_p_one;
			int num_vfs_before = 0;
			int candidate_slave_gid;

			/* Calculate how many VFs are on the previous port, if exists */
			for (i = 1; i < port; i++) {
				bitmap_zero(exclusive_ports.ports, dev->caps.num_ports);
				set_bit(i - 1, exclusive_ports.ports);
				slaves_pport_actv =
					mlx4_phys_to_slaves_pport_actv(
							dev, &exclusive_ports);
				num_vfs_before += bitmap_weight(
						slaves_pport_actv.slaves,
						dev->persist->num_vfs + 1);
			}

			/* candidate_slave_gid isn't necessarily the correct slave, but
			 * it has the same number of ports and is assigned to the same
			 * ports as the real slave we're looking for. On dual port VF,
			 * slave_gid = [single port VFs on port <port>] +
			 * [offset of the current slave from the first dual port VF] +
			 * 1 (for the PF).
			 */
			candidate_slave_gid = slave_gid + num_vfs_before;

			actv_ports = mlx4_get_active_ports(dev, candidate_slave_gid);
			max_port_p_one = find_first_bit(
				actv_ports.ports, dev->caps.num_ports) +
				bitmap_weight(actv_ports.ports,
					      dev->caps.num_ports) + 1;

			/* Calculate the real slave number */
			for (i = 1; i < max_port_p_one; i++) {
				if (i == port)
					continue;
				bitmap_zero(exclusive_ports.ports,
					    dev->caps.num_ports);
				set_bit(i - 1, exclusive_ports.ports);
				slaves_pport_actv =
					mlx4_phys_to_slaves_pport_actv(
						dev, &exclusive_ports);
				slave_gid += bitmap_weight(
						slaves_pport_actv.slaves,
						dev->persist->num_vfs + 1);
			}
		}
		*slave_id = slave_gid;
	}

	return (found_ix >= 0) ? 0 : -EINVAL;
}