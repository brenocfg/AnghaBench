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
struct cache_ht_item_data_ {size_t key_size; int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
ht_items_cmp_func(const void *p1, const void *p2)
{
    	struct cache_ht_item_data_ *hp1, *hp2;
	size_t min_size;
	int result;

	hp1 = (struct cache_ht_item_data_ *)p1;
	hp2 = (struct cache_ht_item_data_ *)p2;

	assert(hp1->key != NULL);
	assert(hp2->key != NULL);

	if (hp1->key_size != hp2->key_size) {
		min_size = (hp1->key_size < hp2->key_size) ? hp1->key_size :
			hp2->key_size;
		result = memcmp(hp1->key, hp2->key, min_size);

		if (result == 0)
			return ((hp1->key_size < hp2->key_size) ? -1 : 1);
		else
			return (result);
	} else
		return (memcmp(hp1->key, hp2->key, hp1->key_size));
}