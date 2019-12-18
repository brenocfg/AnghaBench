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
struct configuration {size_t entries_size; struct configuration_entry** entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (struct configuration_entry* (*) (struct configuration*,size_t)) ; 
 int /*<<< orphan*/  TRACE_OUT (struct configuration_entry* (*) (struct configuration*,size_t)) ; 
 int /*<<< orphan*/  assert (int) ; 

struct configuration_entry *
configuration_get_entry(struct configuration *config, size_t index)
{
	TRACE_IN(configuration_get_entry);
	assert(config != NULL);
	assert(index < config->entries_size);
	TRACE_OUT(configuration_get_entry);
	return (config->entries[index]);
}