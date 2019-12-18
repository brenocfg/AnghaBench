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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  port; } ;
struct TYPE_6__ {TYPE_2__ port_mgmt_change; } ;
struct mlx4_eqe {TYPE_3__ event; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
struct mlx4_dev {TYPE_1__* persist; } ;
struct TYPE_4__ {int num_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_DEV_PMC_SUBTYPE_GUID_INFO ; 
 int /*<<< orphan*/  MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT ; 
 int /*<<< orphan*/  memset (struct mlx4_eqe*,int /*<<< orphan*/ ,int) ; 
 int mlx4_GEN_EQE (struct mlx4_dev*,int,struct mlx4_eqe*) ; 
 int /*<<< orphan*/  mlx4_phys_to_slave_port (struct mlx4_dev*,int,int /*<<< orphan*/ ) ; 

int mlx4_gen_guid_change_eqe(struct mlx4_dev *dev, int slave, u8 port)
{
	struct mlx4_eqe eqe;

	/*don't send if we don't have the that slave */
	if (dev->persist->num_vfs < slave)
		return 0;
	memset(&eqe, 0, sizeof eqe);

	eqe.type = MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT;
	eqe.subtype = MLX4_DEV_PMC_SUBTYPE_GUID_INFO;
	eqe.event.port_mgmt_change.port = mlx4_phys_to_slave_port(dev, slave, port);

	return mlx4_GEN_EQE(dev, slave, &eqe);
}