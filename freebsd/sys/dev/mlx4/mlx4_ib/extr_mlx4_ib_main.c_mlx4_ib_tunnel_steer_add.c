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
struct TYPE_6__ {int /*<<< orphan*/  dst_mac; } ;
struct TYPE_7__ {TYPE_2__ val; } ;
union ib_flow_spec {scalar_t__ type; TYPE_3__ eth; } ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {scalar_t__ tunnel_offload_mode; scalar_t__ dmfs_high_steer_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct ib_qp {int /*<<< orphan*/  qp_num; int /*<<< orphan*/  device; } ;
struct ib_flow_attr {int num_of_specs; int priority; int /*<<< orphan*/  port; } ;
struct TYPE_8__ {struct mlx4_dev* dev; } ;

/* Variables and functions */
 scalar_t__ IB_FLOW_SPEC_ETH ; 
 int MLX4_DOMAIN_UVERBS ; 
 scalar_t__ MLX4_STEERING_DMFS_A0_STATIC ; 
 scalar_t__ MLX4_TUNNEL_OFFLOAD_MODE_VXLAN ; 
 int mlx4_tunnel_steer_add (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_4__* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_ib_tunnel_steer_add(struct ib_qp *qp, struct ib_flow_attr *flow_attr,
				    u64 *reg_id)
{
	void *ib_flow;
	union ib_flow_spec *ib_spec;
	struct mlx4_dev	*dev = to_mdev(qp->device)->dev;
	int err = 0;

	if (dev->caps.tunnel_offload_mode != MLX4_TUNNEL_OFFLOAD_MODE_VXLAN ||
	    dev->caps.dmfs_high_steer_mode == MLX4_STEERING_DMFS_A0_STATIC)
		return 0; /* do nothing */

	ib_flow = flow_attr + 1;
	ib_spec = (union ib_flow_spec *)ib_flow;

	if (ib_spec->type !=  IB_FLOW_SPEC_ETH || flow_attr->num_of_specs != 1)
		return 0; /* do nothing */

	err = mlx4_tunnel_steer_add(to_mdev(qp->device)->dev, ib_spec->eth.val.dst_mac,
				    flow_attr->port, qp->qp_num,
				    MLX4_DOMAIN_UVERBS | (flow_attr->priority & 0xff),
				    reg_id);
	return err;
}