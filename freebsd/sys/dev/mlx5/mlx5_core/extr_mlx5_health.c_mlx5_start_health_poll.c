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
struct mlx5_core_health {int /*<<< orphan*/  timer; int /*<<< orphan*/ * health_counter; int /*<<< orphan*/ * health; int /*<<< orphan*/  flags; int /*<<< orphan*/  fatal_error; } ;
struct TYPE_3__ {struct mlx5_core_health health; } ;
struct mlx5_core_dev {TYPE_2__* iseg; TYPE_1__ priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  health_counter; int /*<<< orphan*/  health; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_DROP_NEW_HEALTH_WORK ; 
 int /*<<< orphan*/  MLX5_DROP_NEW_RECOVERY_WORK ; 
 int /*<<< orphan*/  MLX5_DROP_NEW_WATCHDOG_WORK ; 
 scalar_t__ MLX5_HEALTH_POLL_INTERVAL ; 
 int /*<<< orphan*/  MLX5_SENSOR_NO_ERR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mlx5_trigger_health_watchdog (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_health ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

void mlx5_start_health_poll(struct mlx5_core_dev *dev)
{
	struct mlx5_core_health *health = &dev->priv.health;

	init_timer(&health->timer);
	health->fatal_error = MLX5_SENSOR_NO_ERR;
	clear_bit(MLX5_DROP_NEW_HEALTH_WORK, &health->flags);
	clear_bit(MLX5_DROP_NEW_RECOVERY_WORK, &health->flags);
	clear_bit(MLX5_DROP_NEW_WATCHDOG_WORK, &health->flags);
	health->health = &dev->iseg->health;
	health->health_counter = &dev->iseg->health_counter;

	setup_timer(&health->timer, poll_health, (unsigned long)dev);
	mod_timer(&health->timer,
		  round_jiffies(jiffies + MLX5_HEALTH_POLL_INTERVAL));

	/* do initial PCI power state readout */
	mlx5_trigger_health_watchdog(dev);
}