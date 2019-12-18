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
typedef  int /*<<< orphan*/  uint32_t ;
struct mlx5_spinlock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_spin_lock (struct mlx5_spinlock*) ; 
 int /*<<< orphan*/  mlx5_spin_unlock (struct mlx5_spinlock*) ; 

__attribute__((used)) static inline void mlx5_write64(uint32_t val[2], void *dest, struct mlx5_spinlock *lock)
{
	mlx5_spin_lock(lock);
	*(volatile uint32_t *)dest		= val[0];
	*(volatile uint32_t *)(dest + 4)	= val[1];
	mlx5_spin_unlock(lock);
}