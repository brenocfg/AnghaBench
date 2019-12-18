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
struct sense_key_table_entry {int sense_key; } ;

/* Variables and functions */

__attribute__((used)) static int
senseentrycomp(const void *key, const void *member)
{
	int sense_key;
	const struct sense_key_table_entry *table_entry;

	sense_key = *((const int *)key);
	table_entry = (const struct sense_key_table_entry *)member;

	if (sense_key >= table_entry->sense_key) {
		if (sense_key == table_entry->sense_key)
			return (0);
		return (1);
	}
	return (-1);
}