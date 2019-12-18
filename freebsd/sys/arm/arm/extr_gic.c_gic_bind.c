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
typedef  size_t uint32_t ;
typedef  scalar_t__ u_int ;
struct arm_gic_softc {int dummy; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 scalar_t__ CPU_ISSET (size_t,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 scalar_t__ GICD_ITARGETSR (int /*<<< orphan*/ ) ; 
 size_t MAXCPU ; 
 size_t* arm_gic_map ; 
 int /*<<< orphan*/  gic_d_write_1 (struct arm_gic_softc*,scalar_t__,size_t) ; 
 size_t min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_ncpus ; 

__attribute__((used)) static int
gic_bind(struct arm_gic_softc *sc, u_int irq, cpuset_t *cpus)
{
	uint32_t cpu, end, mask;

	end = min(mp_ncpus, 8);
	for (cpu = end; cpu < MAXCPU; cpu++)
		if (CPU_ISSET(cpu, cpus))
			return (EINVAL);

	for (mask = 0, cpu = 0; cpu < end; cpu++)
		if (CPU_ISSET(cpu, cpus))
			mask |= arm_gic_map[cpu];

	gic_d_write_1(sc, GICD_ITARGETSR(0) + irq, mask);
	return (0);
}