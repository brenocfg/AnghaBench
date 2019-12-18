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
struct mlx5_spinlock {int in_use; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  atomic_thread_fence (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memory_order_acq_rel ; 
 int /*<<< orphan*/  mlx5_single_threaded ; 
 int pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int mlx5_spin_lock(struct mlx5_spinlock *lock)
{
	if (!mlx5_single_threaded)
		return pthread_spin_lock(&lock->lock);

	if (unlikely(lock->in_use)) {
		fprintf(stderr, "*** ERROR: multithreading vilation ***\n"
			"You are running a multithreaded application but\n"
			"you set MLX5_SINGLE_THREADED=1. Please unset it.\n");
		abort();
	} else {
		lock->in_use = 1;
		/*
		 * This fence is not at all correct, but it increases the
		 * chance that in_use is detected by another thread without
		 * much runtime cost. */
		atomic_thread_fence(memory_order_acq_rel);
	}

	return 0;
}