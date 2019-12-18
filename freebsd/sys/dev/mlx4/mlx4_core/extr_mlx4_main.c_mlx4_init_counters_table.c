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
struct mlx4_priv {int /*<<< orphan*/  counters_bitmap; } ;
struct TYPE_2__ {int flags; int max_counters; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOSPC ; 
 int MLX4_DEV_CAP_FLAG_COUNTERS ; 
 int mlx4_bitmap_init (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int roundup_pow_of_two (int) ; 

__attribute__((used)) static int mlx4_init_counters_table(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int nent_pow2;

	if (!(dev->caps.flags & MLX4_DEV_CAP_FLAG_COUNTERS))
		return -ENOENT;

	if (!dev->caps.max_counters)
		return -ENOSPC;

	nent_pow2 = roundup_pow_of_two(dev->caps.max_counters);
	/* reserve last counter index for sink counter */
	return mlx4_bitmap_init(&priv->counters_bitmap, nent_pow2,
				nent_pow2 - 1, 0,
				nent_pow2 - dev->caps.max_counters + 1);
}