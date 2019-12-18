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
struct hash_table {struct hash_bucket** buckets; int /*<<< orphan*/  hash_count; } ;
struct hash_bucket {int len; void* value; int /*<<< orphan*/  name; struct hash_bucket* next; } ;

/* Variables and functions */
 int do_hash (unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int strlen (char*) ; 

void *
hash_lookup(struct hash_table *table, unsigned char *name, int len)
{
	struct hash_bucket *bp;
	int hashno;

	if (!table)
		return (NULL);

	if (!len)
		len = strlen((char *)name);

	hashno = do_hash(name, len, table->hash_count);

	for (bp = table->buckets[hashno]; bp; bp = bp->next)
		if (len == bp->len && !memcmp(bp->name, name, len))
			return (bp->value);

	return (NULL);
}