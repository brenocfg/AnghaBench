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
struct mlx5e_channel_param {int /*<<< orphan*/  tx_cq; } ;
struct mlx5e_channel {TYPE_1__* sq; int /*<<< orphan*/  ix; TYPE_2__* priv; } ;
struct TYPE_4__ {int num_tc; } ;
struct TYPE_3__ {int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_close_cq (int /*<<< orphan*/ *) ; 
 int mlx5e_open_cq (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_tx_cq_comp ; 

__attribute__((used)) static int
mlx5e_open_tx_cqs(struct mlx5e_channel *c,
    struct mlx5e_channel_param *cparam)
{
	int err;
	int tc;

	for (tc = 0; tc < c->priv->num_tc; tc++) {
		/* open completion queue */
		err = mlx5e_open_cq(c->priv, &cparam->tx_cq, &c->sq[tc].cq,
		    &mlx5e_tx_cq_comp, c->ix);
		if (err)
			goto err_close_tx_cqs;
	}
	return (0);

err_close_tx_cqs:
	for (tc--; tc >= 0; tc--)
		mlx5e_close_cq(&c->sq[tc].cq);

	return (err);
}