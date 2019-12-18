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
struct tree_content {unsigned int entry_count; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_tree_content (struct tree_content*) ; 
 int /*<<< orphan*/  release_tree_entry (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_tree_content_recursive(struct tree_content *t)
{
	unsigned int i;
	for (i = 0; i < t->entry_count; i++)
		release_tree_entry(t->entries[i]);
	release_tree_content(t);
}