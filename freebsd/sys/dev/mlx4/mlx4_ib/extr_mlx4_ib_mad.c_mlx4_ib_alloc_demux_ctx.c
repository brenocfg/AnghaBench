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
typedef  int /*<<< orphan*/  u16 ;
struct mlx4_ib_dev {TYPE_3__* dev; int /*<<< orphan*/  ib_dev; } ;
struct mlx4_ib_demux_pv_ctx {int dummy; } ;
struct mlx4_ib_demux_ctx {int port; int /*<<< orphan*/ * tun; int /*<<< orphan*/ * wq; void* ud_wq; int /*<<< orphan*/ * ib_dev; struct mlx4_ib_dev* dev; } ;
struct mlx4_active_ports {int /*<<< orphan*/  ports; } ;
struct TYPE_5__ {int sqp_demux; } ;
struct TYPE_6__ {TYPE_2__ caps; TYPE_1__* persist; } ;
struct TYPE_4__ {scalar_t__ num_vfs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 void* alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int alloc_pv_object (struct mlx4_ib_dev*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pv_object (struct mlx4_ib_dev*,int,int) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 struct mlx4_active_ports mlx4_get_active_ports (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mlx4_ib_mcg_port_cleanup (struct mlx4_ib_demux_ctx*,int) ; 
 int mlx4_ib_mcg_port_init (struct mlx4_ib_demux_ctx*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_ib_alloc_demux_ctx(struct mlx4_ib_dev *dev,
				       struct mlx4_ib_demux_ctx *ctx,
				       int port)
{
	char name[12];
	int ret = 0;
	int i;

	ctx->tun = kcalloc(dev->dev->caps.sqp_demux,
			   sizeof (struct mlx4_ib_demux_pv_ctx *), GFP_KERNEL);
	if (!ctx->tun)
		return -ENOMEM;

	ctx->dev = dev;
	ctx->port = port;
	ctx->ib_dev = &dev->ib_dev;

	for (i = 0;
	     i < min(dev->dev->caps.sqp_demux,
	     (u16)(dev->dev->persist->num_vfs + 1));
	     i++) {
		struct mlx4_active_ports actv_ports =
			mlx4_get_active_ports(dev->dev, i);

		if (!test_bit(port - 1, actv_ports.ports))
			continue;

		ret = alloc_pv_object(dev, i, port, &ctx->tun[i]);
		if (ret) {
			ret = -ENOMEM;
			goto err_mcg;
		}
	}

	ret = mlx4_ib_mcg_port_init(ctx);
	if (ret) {
		pr_err("Failed initializing mcg para-virt (%d)\n", ret);
		goto err_mcg;
	}

	snprintf(name, sizeof name, "mlx4_ibt%d", port);
	ctx->wq = alloc_ordered_workqueue(name, WQ_MEM_RECLAIM);
	if (!ctx->wq) {
		pr_err("Failed to create tunnelling WQ for port %d\n", port);
		ret = -ENOMEM;
		goto err_wq;
	}

	snprintf(name, sizeof name, "mlx4_ibud%d", port);
	ctx->ud_wq = alloc_ordered_workqueue(name, WQ_MEM_RECLAIM);
	if (!ctx->ud_wq) {
		pr_err("Failed to create up/down WQ for port %d\n", port);
		ret = -ENOMEM;
		goto err_udwq;
	}

	return 0;

err_udwq:
	destroy_workqueue(ctx->wq);
	ctx->wq = NULL;

err_wq:
	mlx4_ib_mcg_port_cleanup(ctx, 1);
err_mcg:
	for (i = 0; i < dev->dev->caps.sqp_demux; i++)
		free_pv_object(dev, i, port);
	kfree(ctx->tun);
	ctx->tun = NULL;
	return ret;
}