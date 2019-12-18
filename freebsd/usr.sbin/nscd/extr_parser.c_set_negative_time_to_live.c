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
struct timeval {int tv_sec; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_lifetime; } ;
struct configuration_entry {TYPE_1__ negative_cache_params; } ;
struct configuration {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct configuration*,char const*,int)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct configuration*,char const*,int)) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct configuration_entry* find_create_entry (struct configuration*,char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct timeval*,int) ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
set_negative_time_to_live(struct configuration *config,
	const char *entry_name, int nttl)
{
	struct configuration_entry *entry;
	struct timeval lifetime;

	TRACE_IN(set_negative_time_to_live);
	assert(nttl > 0);
	assert(entry_name != NULL);
	memset(&lifetime, 0, sizeof(struct timeval));
	lifetime.tv_sec = nttl;

	entry = find_create_entry(config, entry_name);
	assert(entry != NULL);
	memcpy(&entry->negative_cache_params.max_lifetime,
		&lifetime, sizeof(struct timeval));

	TRACE_OUT(set_negative_time_to_live);
}