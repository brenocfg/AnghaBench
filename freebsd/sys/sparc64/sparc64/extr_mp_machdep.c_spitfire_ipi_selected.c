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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_FFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spitfire_ipi_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spitfire_ipi_selected(cpuset_t cpus, u_long d0, u_long d1, u_long d2)
{
	u_int cpu;

	while ((cpu = CPU_FFS(&cpus)) != 0) {
		cpu--;
		CPU_CLR(cpu, &cpus);
		spitfire_ipi_single(cpu, d0, d1, d2);
	}
}