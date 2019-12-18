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
struct mlx4_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  ctx_list; } ;
struct mlx4_interface {int /*<<< orphan*/  (* activate ) (int /*<<< orphan*/ *,scalar_t__) ;scalar_t__ (* add ) (int /*<<< orphan*/ *) ;} ;
struct mlx4_device_context {scalar_t__ context; int /*<<< orphan*/  list; struct mlx4_interface* intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET_QUIET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlx4_device_context*) ; 
 struct mlx4_device_context* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vnet0 ; 

__attribute__((used)) static void mlx4_add_device(struct mlx4_interface *intf, struct mlx4_priv *priv)
{
	struct mlx4_device_context *dev_ctx;

	dev_ctx = kmalloc(sizeof *dev_ctx, GFP_KERNEL);
	if (!dev_ctx)
		return;

	dev_ctx->intf    = intf;
	dev_ctx->context = intf->add(&priv->dev);

	if (dev_ctx->context) {
		spin_lock_irq(&priv->ctx_lock);
		list_add_tail(&dev_ctx->list, &priv->ctx_list);
		spin_unlock_irq(&priv->ctx_lock);
		if (intf->activate) {
			CURVNET_SET_QUIET(vnet0);
			intf->activate(&priv->dev, dev_ctx->context);
			CURVNET_RESTORE();
		}
	} else
		kfree(dev_ctx);
}