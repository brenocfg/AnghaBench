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
typedef  int uint16_t ;
struct pt_iscache_entry {int dummy; } ;
struct pt_image_section_cache {int capacity; struct pt_iscache_entry* entries; } ;

/* Variables and functions */
 int pte_internal ; 
 int pte_nomem ; 
 struct pt_iscache_entry* realloc (struct pt_iscache_entry*,int) ; 

__attribute__((used)) static int pt_iscache_expand(struct pt_image_section_cache *iscache)
{
	struct pt_iscache_entry *entries;
	uint16_t capacity, target;

	if (!iscache)
		return -pte_internal;

	capacity = iscache->capacity;
	target = capacity + 8;

	/* Check for overflows. */
	if (target < capacity)
		return -pte_nomem;

	entries = realloc(iscache->entries, target * sizeof(*entries));
	if (!entries)
		return -pte_nomem;

	iscache->capacity = target;
	iscache->entries = entries;
	return 0;
}