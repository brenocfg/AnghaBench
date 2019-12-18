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
struct hash_table {int /*<<< orphan*/ * buckets; } ;
struct hash_bucket {int dummy; } ;

/* Variables and functions */
 int DEFAULT_HASH_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct hash_table* new_hash_table (int) ; 

struct hash_table *
new_hash(void)
{
	struct hash_table *rv = new_hash_table(DEFAULT_HASH_SIZE);

	if (!rv)
		return (rv);
	memset(&rv->buckets[0], 0,
	    DEFAULT_HASH_SIZE * sizeof(struct hash_bucket *));
	return (rv);
}