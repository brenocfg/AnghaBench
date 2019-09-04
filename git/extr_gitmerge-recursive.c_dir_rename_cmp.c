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
struct dir_rename_entry {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dir_rename_cmp(const void *unused_cmp_data,
			  const void *entry,
			  const void *entry_or_key,
			  const void *unused_keydata)
{
	const struct dir_rename_entry *e1 = entry;
	const struct dir_rename_entry *e2 = entry_or_key;

	return strcmp(e1->dir, e2->dir);
}