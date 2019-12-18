#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx4_priv {int /*<<< orphan*/  xrcd_bitmap; } ;
struct TYPE_2__ {scalar_t__ reserved_xrcds; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int mlx4_bitmap_init (int /*<<< orphan*/ *,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_init_xrcd_table(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	return mlx4_bitmap_init(&priv->xrcd_bitmap, (1 << 16),
				(1 << 16) - 1, dev->caps.reserved_xrcds + 1, 0);
}