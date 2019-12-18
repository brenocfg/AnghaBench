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
struct TYPE_2__ {int confidence_threshold; } ;
struct configuration_entry {TYPE_1__ negative_cache_params; } ;
struct configuration {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_OUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct configuration_entry* find_create_entry (struct configuration*,char const*) ; 
 int /*<<< orphan*/  set_negative_conf_thresh ; 

__attribute__((used)) static void
set_negative_confidence_threshold(struct configuration *config,
	const char *entry_name, int conf_thresh)
{
	struct configuration_entry *entry;

	TRACE_IN(set_negative_conf_thresh);
	assert(conf_thresh > 0);
	assert(entry_name != NULL);
	entry = find_create_entry(config, entry_name);
	assert(entry != NULL);
	entry->negative_cache_params.confidence_threshold = conf_thresh;
	TRACE_OUT(set_negative_conf_thresh);
}