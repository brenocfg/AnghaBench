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
struct patch {unsigned long addr; size_t sz; void const* data; int /*<<< orphan*/  cpu_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONFIG_SMP ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  local_patch_text (unsigned long,void const*,size_t) ; 
 int /*<<< orphan*/  patch_text_stop_machine ; 
 int /*<<< orphan*/  stop_machine_cpuslocked (int /*<<< orphan*/ ,struct patch*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void patch_text(unsigned long addr, const void *data, size_t sz)
{
	if (IS_ENABLED(CONFIG_SMP)) {
		struct patch patch = {
			.cpu_count = ATOMIC_INIT(0),
			.addr = addr,
			.sz = sz,
			.data = data,
		};
		stop_machine_cpuslocked(patch_text_stop_machine,
					&patch, NULL);
	} else {
		unsigned long flags;

		local_irq_save(flags);
		local_patch_text(addr, data, sz);
		local_irq_restore(flags);
	}
}