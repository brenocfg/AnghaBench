#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int max_elemsize; } ;
struct TYPE_4__ {int max_elemsize; } ;
struct configuration_entry {TYPE_1__ negative_cache_params; TYPE_2__ positive_cache_params; } ;
struct configuration {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct configuration*,char const*,int)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct configuration*,char const*,int)) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct configuration_entry* find_create_entry (struct configuration*,char const*) ; 

__attribute__((used)) static void
set_keep_hot_count(struct configuration *config,
	const char *entry_name, int count)
{
	struct configuration_entry *entry;

	TRACE_IN(set_keep_hot_count);
	assert(count >= 0);
	assert(entry_name != NULL);

	entry = find_create_entry(config, entry_name);
	assert(entry != NULL);
	entry->positive_cache_params.max_elemsize = count;

	entry = find_create_entry(config, entry_name);
	assert(entry != NULL);
	entry->negative_cache_params.max_elemsize = count;

	TRACE_OUT(set_keep_hot_count);
}