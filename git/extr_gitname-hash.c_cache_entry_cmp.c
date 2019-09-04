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
struct cache_entry {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int cache_entry_cmp(const void *unused_cmp_data,
			   const void *entry,
			   const void *entry_or_key,
			   const void *remove)
{
	const struct cache_entry *ce1 = entry;
	const struct cache_entry *ce2 = entry_or_key;
	/*
	 * For remove_name_hash, find the exact entry (pointer equality); for
	 * index_file_exists, find all entries with matching hash code and
	 * decide whether the entry matches in same_name.
	 */
	return remove ? !(ce1 == ce2) : 0;
}