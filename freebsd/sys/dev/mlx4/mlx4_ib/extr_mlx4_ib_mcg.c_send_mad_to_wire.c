#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx4_ib_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  sm_lock; int /*<<< orphan*/ * sm_ah; } ;
struct mlx4_ib_demux_ctx {int port; struct mlx4_ib_dev* dev; } ;
struct ib_mad {int dummy; } ;
struct ib_ah_attr {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IB_QP1_QKEY ; 
 int /*<<< orphan*/  IB_QPT_GSI ; 
 int /*<<< orphan*/  mlx4_ib_query_ah (int /*<<< orphan*/ ,struct ib_ah_attr*) ; 
 int mlx4_ib_send_to_wire (struct mlx4_ib_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ib_ah_attr*,int /*<<< orphan*/ *,int,struct ib_mad*) ; 
 int /*<<< orphan*/  mlx4_master_func_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int send_mad_to_wire(struct mlx4_ib_demux_ctx *ctx, struct ib_mad *mad)
{
	struct mlx4_ib_dev *dev = ctx->dev;
	struct ib_ah_attr	ah_attr;
	unsigned long flags;

	spin_lock_irqsave(&dev->sm_lock, flags);
	if (!dev->sm_ah[ctx->port - 1]) {
		/* port is not yet Active, sm_ah not ready */
		spin_unlock_irqrestore(&dev->sm_lock, flags);
		return -EAGAIN;
	}
	mlx4_ib_query_ah(dev->sm_ah[ctx->port - 1], &ah_attr);
	spin_unlock_irqrestore(&dev->sm_lock, flags);
	return mlx4_ib_send_to_wire(dev, mlx4_master_func_num(dev->dev),
				    ctx->port, IB_QPT_GSI, 0, 1, IB_QP1_QKEY,
				    &ah_attr, NULL, 0xffff, mad);
}