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
typedef  int /*<<< orphan*/  u32 ;
struct cpu_cacheinfo {unsigned int num_leaves; struct cacheinfo* info_list; } ;
struct cacheinfo {int /*<<< orphan*/  level; int /*<<< orphan*/  type; } ;
struct acpi_table_header {int dummy; } ;
struct acpi_pptt_processor {int dummy; } ;
struct acpi_pptt_cache {int dummy; } ;

/* Variables and functions */
 struct acpi_pptt_cache* acpi_find_cache_node (struct acpi_table_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_pptt_processor**) ; 
 int /*<<< orphan*/  get_acpi_id_for_cpu (unsigned int) ; 
 struct cpu_cacheinfo* get_cpu_cacheinfo (unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct acpi_pptt_cache*,struct acpi_pptt_processor*) ; 
 int /*<<< orphan*/  update_cache_properties (struct cacheinfo*,struct acpi_pptt_cache*,struct acpi_pptt_processor*) ; 

__attribute__((used)) static void cache_setup_acpi_cpu(struct acpi_table_header *table,
				 unsigned int cpu)
{
	struct acpi_pptt_cache *found_cache;
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	u32 acpi_cpu_id = get_acpi_id_for_cpu(cpu);
	struct cacheinfo *this_leaf;
	unsigned int index = 0;
	struct acpi_pptt_processor *cpu_node = NULL;

	while (index < get_cpu_cacheinfo(cpu)->num_leaves) {
		this_leaf = this_cpu_ci->info_list + index;
		found_cache = acpi_find_cache_node(table, acpi_cpu_id,
						   this_leaf->type,
						   this_leaf->level,
						   &cpu_node);
		pr_debug("found = %p %p\n", found_cache, cpu_node);
		if (found_cache)
			update_cache_properties(this_leaf,
						found_cache,
						cpu_node);

		index++;
	}
}