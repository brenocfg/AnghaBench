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
struct TYPE_2__ {struct mlx4_eq* eq; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_priv {TYPE_1__ eq_table; struct mlx4_dev dev; } ;
struct mlx4_eq {int /*<<< orphan*/  affinity_cpu_id; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int bind_irq_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int) ; 

__attribute__((used)) static void mlx4_set_eq_affinity_hint(struct mlx4_priv *priv, int vec)
{
	int hint_err;
	struct mlx4_dev *dev = &priv->dev;
	struct mlx4_eq *eq = &priv->eq_table.eq[vec];

	hint_err = bind_irq_to_cpu(eq->irq, eq->affinity_cpu_id);

	if (hint_err)
		mlx4_warn(dev, "bind_irq_to_cpu failed, err %d\n", hint_err);
}