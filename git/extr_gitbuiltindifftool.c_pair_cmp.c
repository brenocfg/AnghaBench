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
struct pair_entry {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pair_cmp(const void *unused_cmp_data,
		    const void *entry,
		    const void *entry_or_key,
		    const void *unused_keydata)
{
	const struct pair_entry *a = entry;
	const struct pair_entry *b = entry_or_key;

	return strcmp(a->path, b->path);
}