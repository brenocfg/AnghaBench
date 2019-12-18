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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  changed_attr; } ;
struct TYPE_6__ {TYPE_1__ port_info; } ;
struct TYPE_7__ {TYPE_2__ params; int /*<<< orphan*/  port; } ;
struct TYPE_8__ {TYPE_3__ port_mgmt_change; } ;
struct mlx4_eqe {TYPE_4__ event; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_SLAVES ; 
 int /*<<< orphan*/  MLX4_DEV_PMC_SUBTYPE_PORT_INFO ; 
 int /*<<< orphan*/  MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx4_eqe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  slave_event (struct mlx4_dev*,int /*<<< orphan*/ ,struct mlx4_eqe*) ; 

int mlx4_gen_slaves_port_mgt_ev(struct mlx4_dev *dev, u8 port, int attr)
{
	struct mlx4_eqe eqe;

	memset(&eqe, 0, sizeof eqe);

	eqe.type = MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT;
	eqe.subtype = MLX4_DEV_PMC_SUBTYPE_PORT_INFO;
	eqe.event.port_mgmt_change.port = port;
	eqe.event.port_mgmt_change.params.port_info.changed_attr =
		cpu_to_be32((u32) attr);

	slave_event(dev, ALL_SLAVES, &eqe);
	return 0;
}