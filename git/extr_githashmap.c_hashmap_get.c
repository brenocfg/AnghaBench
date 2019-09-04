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
struct hashmap {int dummy; } ;

/* Variables and functions */
 void** find_entry_ptr (struct hashmap const*,void const*,void const*) ; 

void *hashmap_get(const struct hashmap *map, const void *key, const void *keydata)
{
	return *find_entry_ptr(map, key, keydata);
}