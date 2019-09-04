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
struct dir_entry {scalar_t__ namelen; char const* name; } ;

/* Variables and functions */
 scalar_t__ strncasecmp (char const*,char const*,scalar_t__) ; 

__attribute__((used)) static int dir_entry_cmp(const void *unused_cmp_data,
			 const void *entry,
			 const void *entry_or_key,
			 const void *keydata)
{
	const struct dir_entry *e1 = entry;
	const struct dir_entry *e2 = entry_or_key;
	const char *name = keydata;

	return e1->namelen != e2->namelen || strncasecmp(e1->name,
			name ? name : e2->name, e1->namelen);
}