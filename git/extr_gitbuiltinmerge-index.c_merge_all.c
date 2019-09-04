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
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct cache_entry** active_cache ; 
 int active_nr ; 
 int /*<<< orphan*/  ce_stage (struct cache_entry const*) ; 
 int merge_entry (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void merge_all(void)
{
	int i;
	for (i = 0; i < active_nr; i++) {
		const struct cache_entry *ce = active_cache[i];
		if (!ce_stage(ce))
			continue;
		i += merge_entry(i, ce->name)-1;
	}
}