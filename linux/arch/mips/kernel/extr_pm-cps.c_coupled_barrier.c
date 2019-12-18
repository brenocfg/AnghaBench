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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned int atomic_inc_return (int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coupled_coherence ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static void coupled_barrier(atomic_t *a, unsigned online)
{
	/*
	 * This function is effectively the same as
	 * cpuidle_coupled_parallel_barrier, which can't be used here since
	 * there's no cpuidle device.
	 */

	if (!coupled_coherence)
		return;

	smp_mb__before_atomic();
	atomic_inc(a);

	while (atomic_read(a) < online)
		cpu_relax();

	if (atomic_inc_return(a) == online * 2) {
		atomic_set(a, 0);
		return;
	}

	while (atomic_read(a) > online)
		cpu_relax();
}