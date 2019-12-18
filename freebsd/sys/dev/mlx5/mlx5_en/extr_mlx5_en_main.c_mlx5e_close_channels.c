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
struct TYPE_2__ {int num_channels; } ;
struct mlx5e_priv {int /*<<< orphan*/ * channel; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_close_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_close_channel_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_close_channels(struct mlx5e_priv *priv)
{
	int i;

	for (i = 0; i < priv->params.num_channels; i++)
		mlx5e_close_channel(&priv->channel[i]);
	for (i = 0; i < priv->params.num_channels; i++)
		mlx5e_close_channel_wait(&priv->channel[i]);
}