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
struct hash_table {int hash_count; } ;
struct hash_bucket {int dummy; } ;

/* Variables and functions */
 int DEFAULT_HASH_SIZE ; 
 struct hash_table* calloc (int,int) ; 

struct hash_table *
new_hash_table(int count)
{
	struct hash_table *rval;

	rval = calloc(1, sizeof(struct hash_table) -
	    (DEFAULT_HASH_SIZE * sizeof(struct hash_bucket *)) +
	    (count * sizeof(struct hash_bucket *)));
	if (rval == NULL)
		return (NULL);
	rval->hash_count = count;
	return (rval);
}