#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Hash_Entry {int dummy; } ;
struct TYPE_3__ {int size; int mask; struct Hash_Entry** bucketPtr; scalar_t__ numEntries; } ;
typedef  TYPE_1__ Hash_Table ;

/* Variables and functions */
 scalar_t__ emalloc (int) ; 

void
Hash_InitTable(
	register Hash_Table *t,	/* Structure to use to hold table. */
	int numBuckets)		/* How many buckets to create for starters.
				 * This number is rounded up to a power of
				 * two.   If <= 0, a reasonable default is
				 * chosen. The table will grow in size later
				 * as needed. */
{
	register int i;
	register struct Hash_Entry **hp;

	/*
	 * Round up the size to a power of two.
	 */
	if (numBuckets <= 0)
		i = 16;
	else {
		for (i = 2; i < numBuckets; i <<= 1)
			 continue;
	}
	t->numEntries = 0;
	t->size = i;
	t->mask = i - 1;
	t->bucketPtr = hp = (struct Hash_Entry **)emalloc(sizeof(*hp) * i);
	while (--i >= 0)
		*hp++ = NULL;
}