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
typedef  int uint64_t ;
struct hashmap {int do_count_items; void const* cmpfn_data; scalar_t__ cmpfn; } ;
typedef  scalar_t__ hashmap_cmp_fn ;

/* Variables and functions */
 unsigned int HASHMAP_INITIAL_SIZE ; 
 int HASHMAP_LOAD_FACTOR ; 
 unsigned int HASHMAP_RESIZE_BITS ; 
 int /*<<< orphan*/  alloc_table (struct hashmap*,unsigned int) ; 
 scalar_t__ always_equal ; 
 int /*<<< orphan*/  memset (struct hashmap*,int /*<<< orphan*/ ,int) ; 

void hashmap_init(struct hashmap *map, hashmap_cmp_fn equals_function,
		const void *cmpfn_data, size_t initial_size)
{
	unsigned int size = HASHMAP_INITIAL_SIZE;

	memset(map, 0, sizeof(*map));

	map->cmpfn = equals_function ? equals_function : always_equal;
	map->cmpfn_data = cmpfn_data;

	/* calculate initial table size and allocate the table */
	initial_size = (unsigned int) ((uint64_t) initial_size * 100
			/ HASHMAP_LOAD_FACTOR);
	while (initial_size > size)
		size <<= HASHMAP_RESIZE_BITS;
	alloc_table(map, size);

	/*
	 * Keep track of the number of items in the map and
	 * allow the map to automatically grow as necessary.
	 */
	map->do_count_items = 1;
}