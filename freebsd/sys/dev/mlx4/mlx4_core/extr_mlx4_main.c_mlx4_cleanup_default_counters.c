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
struct mlx4_priv {int* def_counter; } ;
struct TYPE_2__ {int num_ports; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_counter_free (struct mlx4_dev*,int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

__attribute__((used)) static void mlx4_cleanup_default_counters(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int port;

	for (port = 0; port < dev->caps.num_ports; port++)
		if (priv->def_counter[port] != -1)
			mlx4_counter_free(dev,  priv->def_counter[port]);
}