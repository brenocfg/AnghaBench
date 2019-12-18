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
struct property_entry {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct property_entry const*) ; 
 int /*<<< orphan*/  property_entry_free_data (struct property_entry const*) ; 

void property_entries_free(const struct property_entry *properties)
{
	const struct property_entry *p;

	if (!properties)
		return;

	for (p = properties; p->name; p++)
		property_entry_free_data(p);

	kfree(properties);
}