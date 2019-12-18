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
struct mlx5e_channel_param {int /*<<< orphan*/  sq; } ;
struct mlx5e_channel {int /*<<< orphan*/ * sq; TYPE_1__* priv; } ;
struct TYPE_2__ {int num_tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_close_sq_wait (int /*<<< orphan*/ *) ; 
 int mlx5e_open_sq (struct mlx5e_channel*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlx5e_open_sqs(struct mlx5e_channel *c,
    struct mlx5e_channel_param *cparam)
{
	int err;
	int tc;

	for (tc = 0; tc < c->priv->num_tc; tc++) {
		err = mlx5e_open_sq(c, tc, &cparam->sq, &c->sq[tc]);
		if (err)
			goto err_close_sqs;
	}

	return (0);

err_close_sqs:
	for (tc--; tc >= 0; tc--)
		mlx5e_close_sq_wait(&c->sq[tc]);

	return (err);
}