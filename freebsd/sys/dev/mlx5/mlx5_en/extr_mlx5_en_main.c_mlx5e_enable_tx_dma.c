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
struct mlx5e_channel {int /*<<< orphan*/ * sq; TYPE_1__* priv; } ;
struct TYPE_2__ {int num_tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_resume_sq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_enable_tx_dma(struct mlx5e_channel *ch)
{
        int i;

	for (i = 0; i < ch->priv->num_tc; i++)
		mlx5e_resume_sq(&ch->sq[i]);
}