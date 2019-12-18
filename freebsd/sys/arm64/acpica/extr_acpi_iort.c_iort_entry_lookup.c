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
typedef  scalar_t__ u_int ;
struct TYPE_2__ {struct iort_map_entry* mappings; } ;
struct iort_node {int nentries; TYPE_1__ entries; } ;
struct iort_map_entry {scalar_t__ base; scalar_t__ end; int flags; scalar_t__ outbase; struct iort_node* out_node; } ;

/* Variables and functions */
 int ACPI_IORT_ID_SINGLE_MAPPING ; 

__attribute__((used)) static struct iort_node *
iort_entry_lookup(struct iort_node *node, u_int id, u_int *outid)
{
	struct iort_map_entry *entry;
	int i;

	entry = node->entries.mappings;
	for (i = 0; i < node->nentries; i++, entry++) {
		if (entry->base <= id && id <= entry->end)
			break;
	}
	if (i == node->nentries)
		return (NULL);
	if ((entry->flags & ACPI_IORT_ID_SINGLE_MAPPING) == 0)
		*outid =  entry->outbase + (id - entry->base);
	else
		*outid = entry->outbase;
	return (entry->out_node);
}