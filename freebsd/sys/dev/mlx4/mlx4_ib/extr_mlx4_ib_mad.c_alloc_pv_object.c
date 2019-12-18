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
struct mlx4_ib_dev {int /*<<< orphan*/  ib_dev; } ;
struct mlx4_ib_demux_pv_ctx {int port; int slave; int /*<<< orphan*/ * ib_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlx4_ib_demux_pv_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static int alloc_pv_object(struct mlx4_ib_dev *dev, int slave, int port,
			       struct mlx4_ib_demux_pv_ctx **ret_ctx)
{
	struct mlx4_ib_demux_pv_ctx *ctx;

	*ret_ctx = NULL;
	ctx = kzalloc(sizeof (struct mlx4_ib_demux_pv_ctx), GFP_KERNEL);
	if (!ctx) {
		pr_err("failed allocating pv resource context "
		       "for port %d, slave %d\n", port, slave);
		return -ENOMEM;
	}

	ctx->ib_dev = &dev->ib_dev;
	ctx->port = port;
	ctx->slave = slave;
	*ret_ctx = ctx;
	return 0;
}