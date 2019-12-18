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
struct tree_content {scalar_t__ entry_count; int /*<<< orphan*/  entries; int /*<<< orphan*/  delta_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct tree_content* new_tree_content (scalar_t__) ; 
 int /*<<< orphan*/  release_tree_content (struct tree_content*) ; 

__attribute__((used)) static struct tree_content *grow_tree_content(
	struct tree_content *t,
	int amt)
{
	struct tree_content *r = new_tree_content(t->entry_count + amt);
	r->entry_count = t->entry_count;
	r->delta_depth = t->delta_depth;
	COPY_ARRAY(r->entries, t->entries, t->entry_count);
	release_tree_content(t);
	return r;
}