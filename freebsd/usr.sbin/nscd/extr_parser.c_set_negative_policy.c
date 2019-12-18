#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int policy; } ;
struct configuration_entry {TYPE_1__ negative_cache_params; } ;
struct configuration {int dummy; } ;
typedef  enum cache_policy_t { ____Placeholder_cache_policy_t } cache_policy_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct configuration*,char const*,int)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct configuration*,char const*,int)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct configuration_entry* find_create_entry (struct configuration*,char const*) ; 

__attribute__((used)) static void
set_negative_policy(struct configuration *config,
	const char *entry_name, enum cache_policy_t policy)
{
	struct configuration_entry *entry;

	TRACE_IN(set_negative_policy);
	assert(entry_name != NULL);

	entry = find_create_entry(config, entry_name);
	assert(entry != NULL);
	entry->negative_cache_params.policy = policy;

	TRACE_OUT(set_negative_policy);
}