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
struct path_entry {void const* path; } ;

/* Variables and functions */
 int strcmp (void const*,void const*) ; 

__attribute__((used)) static int path_entry_cmp(const void *unused_cmp_data,
			  const void *entry,
			  const void *entry_or_key,
			  const void *key)
{
	const struct path_entry *a = entry;
	const struct path_entry *b = entry_or_key;

	return strcmp(a->path, key ? key : b->path);
}