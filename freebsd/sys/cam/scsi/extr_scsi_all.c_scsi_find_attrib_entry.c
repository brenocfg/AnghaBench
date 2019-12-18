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
typedef  size_t uint32_t ;
struct scsi_attrib_table_entry {size_t id; } ;

/* Variables and functions */

struct scsi_attrib_table_entry *
scsi_find_attrib_entry(struct scsi_attrib_table_entry *table,
		       size_t num_table_entries, uint32_t id)
{
	uint32_t i;

	for (i = 0; i < num_table_entries; i++) {
		if (table[i].id == id)
			return (&table[i]);
	}

	return (NULL);
}