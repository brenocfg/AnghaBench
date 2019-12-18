#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* clusters; } ;
struct TYPE_5__ {TYPE_1__* cpus; } ;
struct TYPE_4__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_GOING_DOWN ; 
 TYPE_3__ mcpm_sync ; 
 int /*<<< orphan*/  sync_cache_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __mcpm_cpu_going_down(unsigned int cpu, unsigned int cluster)
{
	mcpm_sync.clusters[cluster].cpus[cpu].cpu = CPU_GOING_DOWN;
	sync_cache_w(&mcpm_sync.clusters[cluster].cpus[cpu].cpu);
}