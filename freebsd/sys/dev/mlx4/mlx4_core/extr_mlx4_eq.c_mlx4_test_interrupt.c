#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* eq; } ;
struct mlx4_priv {TYPE_2__ eq_table; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  eqn; } ;

/* Variables and functions */
 size_t MLX4_CQ_TO_EQ_VECTOR (int) ; 
 size_t MLX4_EQ_ASYNC ; 
 int /*<<< orphan*/  get_async_ev_mask (struct mlx4_dev*) ; 
 int mlx4_MAP_EQ (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_NOP (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cmd_use_events (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cmd_use_polling (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*) ; 

int mlx4_test_interrupt(struct mlx4_dev *dev, int vector)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int err;

	/* Temporary use polling for command completions */
	mlx4_cmd_use_polling(dev);

	/* Map the new eq to handle all asynchronous events */
	err = mlx4_MAP_EQ(dev, get_async_ev_mask(dev), 0,
			  priv->eq_table.eq[MLX4_CQ_TO_EQ_VECTOR(vector)].eqn);
	if (err) {
		mlx4_warn(dev, "Failed mapping eq for interrupt test\n");
		goto out;
	}

	/* Go back to using events */
	mlx4_cmd_use_events(dev);
	err = mlx4_NOP(dev);

	/* Return to default */
	mlx4_cmd_use_polling(dev);
out:
	mlx4_MAP_EQ(dev, get_async_ev_mask(dev), 0,
		    priv->eq_table.eq[MLX4_EQ_ASYNC].eqn);
	mlx4_cmd_use_events(dev);

	return err;
}