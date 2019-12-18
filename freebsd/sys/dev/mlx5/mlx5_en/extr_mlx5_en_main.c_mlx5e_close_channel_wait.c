#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5e_channel {int /*<<< orphan*/  rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_close_rq_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_close_sqs_wait (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_close_tx_cqs (struct mlx5e_channel*) ; 

__attribute__((used)) static void
mlx5e_close_channel_wait(struct mlx5e_channel *c)
{
	mlx5e_close_rq_wait(&c->rq);
	mlx5e_close_sqs_wait(c);
	mlx5e_close_tx_cqs(c);
}