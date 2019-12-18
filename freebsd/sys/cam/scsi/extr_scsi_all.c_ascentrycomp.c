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
struct asc_table_entry {int asc; int ascq; int action; } ;
struct asc_key {int asc; int ascq; } ;

/* Variables and functions */
 int SSQ_RANGE ; 

__attribute__((used)) static int
ascentrycomp(const void *key, const void *member)
{
	int asc;
	int ascq;
	const struct asc_table_entry *table_entry;

	asc = ((const struct asc_key *)key)->asc;
	ascq = ((const struct asc_key *)key)->ascq;
	table_entry = (const struct asc_table_entry *)member;

	if (asc >= table_entry->asc) {

		if (asc > table_entry->asc)
			return (1);

		if (ascq <= table_entry->ascq) {
			/* Check for ranges */
			if (ascq == table_entry->ascq
		 	 || ((table_entry->action & SSQ_RANGE) != 0
		  	   && ascq >= (table_entry - 1)->ascq))
				return (0);
			return (-1);
		}
		return (1);
	}
	return (-1);
}