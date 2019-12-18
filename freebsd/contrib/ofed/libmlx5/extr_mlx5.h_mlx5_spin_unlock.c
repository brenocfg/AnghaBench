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
struct mlx5_spinlock {scalar_t__ in_use; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_single_threaded ; 
 int pthread_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int mlx5_spin_unlock(struct mlx5_spinlock *lock)
{
	if (!mlx5_single_threaded)
		return pthread_spin_unlock(&lock->lock);

	lock->in_use = 0;

	return 0;
}