#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * sqps; TYPE_2__* demux; } ;
struct mlx4_ib_dev {TYPE_1__ sriov; int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tun; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_vf_mcast (TYPE_2__*,int) ; 
 int create_pv_resources (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_pv_resources (struct mlx4_ib_dev*,int,int,int /*<<< orphan*/ ,int) ; 
 int mlx4_master_func_num (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_ib_tunnels_update(struct mlx4_ib_dev *dev, int slave,
				  int port, int do_init)
{
	int ret = 0;

	if (!do_init) {
		clean_vf_mcast(&dev->sriov.demux[port - 1], slave);
		/* for master, destroy real sqp resources */
		if (slave == mlx4_master_func_num(dev->dev))
			destroy_pv_resources(dev, slave, port,
					     dev->sriov.sqps[port - 1], 1);
		/* destroy the tunnel qp resources */
		destroy_pv_resources(dev, slave, port,
				     dev->sriov.demux[port - 1].tun[slave], 1);
		return 0;
	}

	/* create the tunnel qp resources */
	ret = create_pv_resources(&dev->ib_dev, slave, port, 1,
				  dev->sriov.demux[port - 1].tun[slave]);

	/* for master, create the real sqp resources */
	if (!ret && slave == mlx4_master_func_num(dev->dev))
		ret = create_pv_resources(&dev->ib_dev, slave, port, 0,
					  dev->sriov.sqps[port - 1]);
	return ret;
}