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
struct mlx5e_priv {int num_tc; } ;
struct mlx5e_channel {TYPE_1__* sq; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_update_sq_inline (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_refresh_sq_inline_sub(struct mlx5e_priv *priv, struct mlx5e_channel *c)
{
	int i;

	for (i = 0; i != priv->num_tc; i++) {
		mtx_lock(&c->sq[i].lock);
		mlx5e_update_sq_inline(&c->sq[i]);
		mtx_unlock(&c->sq[i].lock);
	}
}