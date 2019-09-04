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
struct name_entry {int dummy; } ;
struct tree_desc {struct name_entry entry; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ update_tree_entry_gently (struct tree_desc*) ; 

int tree_entry_gently(struct tree_desc *desc, struct name_entry *entry)
{
	if (!desc->size)
		return 0;

	*entry = desc->entry;
	if (update_tree_entry_gently(desc))
		return 0;
	return 1;
}