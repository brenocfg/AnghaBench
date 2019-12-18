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
struct patch {int /*<<< orphan*/  sz; int /*<<< orphan*/  addr; int /*<<< orphan*/  cpu_count; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  __invalidate_icache_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  local_patch_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ num_online_cpus () ; 

__attribute__((used)) static int patch_text_stop_machine(void *data)
{
	struct patch *patch = data;

	if (atomic_inc_return(&patch->cpu_count) == 1) {
		local_patch_text(patch->addr, patch->data, patch->sz);
		atomic_inc(&patch->cpu_count);
	} else {
		while (atomic_read(&patch->cpu_count) <= num_online_cpus())
			cpu_relax();
		__invalidate_icache_range(patch->addr, patch->sz);
	}
	return 0;
}