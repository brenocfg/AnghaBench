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
struct ref_store_hash_entry {void const* name; } ;

/* Variables and functions */
 int strcmp (void const*,char const*) ; 

__attribute__((used)) static int ref_store_hash_cmp(const void *unused_cmp_data,
			      const void *entry, const void *entry_or_key,
			      const void *keydata)
{
	const struct ref_store_hash_entry *e1 = entry, *e2 = entry_or_key;
	const char *name = keydata ? keydata : e2->name;

	return strcmp(e1->name, name);
}