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
struct cpuidle_device {TYPE_1__* coupled; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_2__ {int online_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

void cpuidle_coupled_parallel_barrier(struct cpuidle_device *dev, atomic_t *a)
{
	int n = dev->coupled->online_count;

	smp_mb__before_atomic();
	atomic_inc(a);

	while (atomic_read(a) < n)
		cpu_relax();

	if (atomic_inc_return(a) == n * 2) {
		atomic_set(a, 0);
		return;
	}

	while (atomic_read(a) > n)
		cpu_relax();
}