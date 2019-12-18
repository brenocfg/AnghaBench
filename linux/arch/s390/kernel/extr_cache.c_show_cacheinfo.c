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
struct seq_file {int dummy; } ;
struct cpu_cacheinfo {int num_leaves; struct cacheinfo* info_list; } ;
struct cacheinfo {int level; size_t type; int size; int coherency_line_size; int ways_of_associativity; scalar_t__ disable_sysfs; } ;

/* Variables and functions */
 int* cache_type_string ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_any (int /*<<< orphan*/ ) ; 
 struct cpu_cacheinfo* get_cpu_cacheinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  test_facility (int) ; 

void show_cacheinfo(struct seq_file *m)
{
	struct cpu_cacheinfo *this_cpu_ci;
	struct cacheinfo *cache;
	int idx;

	if (!test_facility(34))
		return;
	this_cpu_ci = get_cpu_cacheinfo(cpumask_any(cpu_online_mask));
	for (idx = 0; idx < this_cpu_ci->num_leaves; idx++) {
		cache = this_cpu_ci->info_list + idx;
		seq_printf(m, "cache%-11d: ", idx);
		seq_printf(m, "level=%d ", cache->level);
		seq_printf(m, "type=%s ", cache_type_string[cache->type]);
		seq_printf(m, "scope=%s ",
			   cache->disable_sysfs ? "Shared" : "Private");
		seq_printf(m, "size=%dK ", cache->size >> 10);
		seq_printf(m, "line_size=%u ", cache->coherency_line_size);
		seq_printf(m, "associativity=%d", cache->ways_of_associativity);
		seq_puts(m, "\n");
	}
}