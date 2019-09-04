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
struct name_entry {int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int base_name_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_entry_len (struct name_entry const*) ; 

__attribute__((used)) static int base_name_entries_compare(const struct name_entry *a,
				     const struct name_entry *b)
{
	return base_name_compare(a->path, tree_entry_len(a), a->mode,
				 b->path, tree_entry_len(b), b->mode);
}