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
struct TYPE_6__ {int /*<<< orphan*/  pool_lock; } ;
struct TYPE_5__ {TYPE_1__* eq; } ;
struct mlx4_priv {TYPE_3__ msix_ctl; TYPE_2__ eq_table; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int MLX4_CQ_TO_EQ_VECTOR (int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx4_release_eq(struct mlx4_dev *dev, int vec)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int eq_vec = MLX4_CQ_TO_EQ_VECTOR(vec);

	mutex_lock(&priv->msix_ctl.pool_lock);
	priv->eq_table.eq[eq_vec].ref_count--;

	/* once we allocated EQ, we don't release it because it might be binded
	 * to cpu_rmap.
	 */
	mutex_unlock(&priv->msix_ctl.pool_lock);
}