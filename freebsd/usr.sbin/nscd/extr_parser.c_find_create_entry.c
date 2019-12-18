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
struct configuration_entry {int dummy; } ;
struct configuration {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (struct configuration_entry* (*) (struct configuration*,char const*)) ; 
 int /*<<< orphan*/  TRACE_OUT (struct configuration_entry* (*) (struct configuration*,char const*)) ; 
 int add_configuration_entry (struct configuration*,struct configuration_entry*) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct configuration_entry* configuration_find_entry (struct configuration*,char const*) ; 
 struct configuration_entry* create_def_configuration_entry (char const*) ; 

__attribute__((used)) static struct configuration_entry *
find_create_entry(struct configuration *config,
	const char *entry_name)
{
	struct configuration_entry *entry = NULL;
	int res;

	TRACE_IN(find_create_entry);
	entry = configuration_find_entry(config, entry_name);
	if (entry == NULL) {
		entry = create_def_configuration_entry(entry_name);
		assert( entry != NULL);
		res = add_configuration_entry(config, entry);
		assert(res == 0);
	}

	TRACE_OUT(find_create_entry);
	return (entry);
}