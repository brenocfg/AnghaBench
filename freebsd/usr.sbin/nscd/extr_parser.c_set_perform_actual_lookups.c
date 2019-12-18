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
struct configuration_entry {int perform_actual_lookups; } ;
struct configuration {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct configuration*,char const*,int)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct configuration*,char const*,int)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct configuration_entry* find_create_entry (struct configuration*,char const*) ; 

__attribute__((used)) static void
set_perform_actual_lookups(struct configuration *config,
	const char *entry_name, int flag)
{
	struct configuration_entry *entry;

	TRACE_IN(set_perform_actual_lookups);
	assert(entry_name != NULL);

	entry = find_create_entry(config, entry_name);
	assert(entry != NULL);
	entry->perform_actual_lookups = flag;

	TRACE_OUT(set_perform_actual_lookups);
}