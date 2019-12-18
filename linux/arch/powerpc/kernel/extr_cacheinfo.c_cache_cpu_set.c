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
struct cache {struct cache* next_local; int /*<<< orphan*/  shared_cpu_map; int /*<<< orphan*/  ofnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_type_string (struct cache*) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cache_cpu_set(struct cache *cache, int cpu)
{
	struct cache *next = cache;

	while (next) {
		WARN_ONCE(cpumask_test_cpu(cpu, &next->shared_cpu_map),
			  "CPU %i already accounted in %pOF(%s)\n",
			  cpu, next->ofnode,
			  cache_type_string(next));
		cpumask_set_cpu(cpu, &next->shared_cpu_map);
		next = next->next_local;
	}
}