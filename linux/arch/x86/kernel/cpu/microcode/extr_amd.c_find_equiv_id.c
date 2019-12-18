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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct equiv_cpu_table {unsigned int num_entries; struct equiv_cpu_entry* entry; } ;
struct equiv_cpu_entry {scalar_t__ installed_cpu; int /*<<< orphan*/  equiv_cpu; } ;

/* Variables and functions */

__attribute__((used)) static u16 find_equiv_id(struct equiv_cpu_table *et, u32 sig)
{
	unsigned int i;

	if (!et || !et->num_entries)
		return 0;

	for (i = 0; i < et->num_entries; i++) {
		struct equiv_cpu_entry *e = &et->entry[i];

		if (sig == e->installed_cpu)
			return e->equiv_cpu;

		e++;
	}
	return 0;
}