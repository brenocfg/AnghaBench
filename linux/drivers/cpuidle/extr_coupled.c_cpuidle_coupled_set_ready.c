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
struct cpuidle_coupled {int /*<<< orphan*/  ready_waiting_counts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_WAITING_CPUS ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cpuidle_coupled_set_ready(struct cpuidle_coupled *coupled)
{
	atomic_add(MAX_WAITING_CPUS, &coupled->ready_waiting_counts);
}