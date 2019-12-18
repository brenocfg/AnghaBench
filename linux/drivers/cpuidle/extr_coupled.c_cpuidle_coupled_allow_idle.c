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
struct cpuidle_coupled {int /*<<< orphan*/  prevent; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuidle_coupled_poke_others (int,struct cpuidle_coupled*) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void cpuidle_coupled_allow_idle(struct cpuidle_coupled *coupled)
{
	int cpu = get_cpu();

	/*
	 * Write barrier ensures readers see the new online_count when they
	 * see prevent == 0.
	 */
	smp_wmb();
	coupled->prevent--;
	/* Force cpus out of the prevent loop. */
	cpuidle_coupled_poke_others(cpu, coupled);
	put_cpu();
}