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
struct mlx5_spinlock {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int pthread_spin_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int mlx5_spinlock_destroy(struct mlx5_spinlock *lock)
{
	return pthread_spin_destroy(&lock->lock);
}