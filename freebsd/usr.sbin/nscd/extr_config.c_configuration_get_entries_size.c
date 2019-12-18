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
struct configuration {size_t entries_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (size_t (*) (struct configuration*)) ; 
 int /*<<< orphan*/  TRACE_OUT (size_t (*) (struct configuration*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

size_t
configuration_get_entries_size(struct configuration *config)
{
	TRACE_IN(configuration_get_entries_size);
	assert(config != NULL);
	TRACE_OUT(configuration_get_entries_size);
	return (config->entries_size);
}