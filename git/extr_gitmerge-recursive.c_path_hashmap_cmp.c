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
struct path_hashmap_entry {char const* path; } ;

/* Variables and functions */
 scalar_t__ ignore_case ; 
 int strcasecmp (char const*,char const*) ; 
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int path_hashmap_cmp(const void *cmp_data,
			    const void *entry,
			    const void *entry_or_key,
			    const void *keydata)
{
	const struct path_hashmap_entry *a = entry;
	const struct path_hashmap_entry *b = entry_or_key;
	const char *key = keydata;

	if (ignore_case)
		return strcasecmp(a->path, key ? key : b->path);
	else
		return strcmp(a->path, key ? key : b->path);
}