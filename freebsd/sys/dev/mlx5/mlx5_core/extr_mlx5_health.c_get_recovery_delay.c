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
struct TYPE_3__ {scalar_t__ fatal_error; } ;
struct TYPE_4__ {TYPE_1__ health; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;

/* Variables and functions */
 unsigned long MLX5_RECOVERY_DELAY_MSECS ; 
 unsigned long MLX5_RECOVERY_NO_DELAY ; 
 scalar_t__ MLX5_SENSOR_PCI_COMM_ERR ; 
 scalar_t__ MLX5_SENSOR_PCI_ERR ; 

__attribute__((used)) static unsigned long get_recovery_delay(struct mlx5_core_dev *dev)
{
	return dev->priv.health.fatal_error == MLX5_SENSOR_PCI_ERR ||
		dev->priv.health.fatal_error == MLX5_SENSOR_PCI_COMM_ERR	?
		MLX5_RECOVERY_DELAY_MSECS : MLX5_RECOVERY_NO_DELAY;
}