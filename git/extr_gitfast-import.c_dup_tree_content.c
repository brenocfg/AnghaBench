#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tree_entry {struct tree_content* tree; TYPE_1__* versions; } ;
struct tree_content {unsigned int entry_count; int /*<<< orphan*/  delta_depth; struct tree_entry** entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct tree_entry*,struct tree_entry*,int) ; 
 struct tree_content* new_tree_content (unsigned int) ; 
 struct tree_entry* new_tree_entry () ; 

__attribute__((used)) static struct tree_content *dup_tree_content(struct tree_content *s)
{
	struct tree_content *d;
	struct tree_entry *a, *b;
	unsigned int i;

	if (!s)
		return NULL;
	d = new_tree_content(s->entry_count);
	for (i = 0; i < s->entry_count; i++) {
		a = s->entries[i];
		b = new_tree_entry();
		memcpy(b, a, sizeof(*a));
		if (a->tree && is_null_oid(&b->versions[1].oid))
			b->tree = dup_tree_content(a->tree);
		else
			b->tree = NULL;
		d->entries[i] = b;
	}
	d->entry_count = s->entry_count;
	d->delta_depth = s->delta_depth;

	return d;
}