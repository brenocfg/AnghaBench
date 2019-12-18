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
struct tree_desc {struct name_entry entry; scalar_t__ size; } ;

/* Variables and functions */
 int base_name_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_entry_len (struct name_entry*) ; 

__attribute__((used)) static int tree_entry_pathcmp(struct tree_desc *t1, struct tree_desc *t2)
{
	struct name_entry *e1, *e2;
	int cmp;

	/* empty descriptors sort after valid tree entries */
	if (!t1->size)
		return t2->size ? 1 : 0;
	else if (!t2->size)
		return -1;

	e1 = &t1->entry;
	e2 = &t2->entry;
	cmp = base_name_compare(e1->path, tree_entry_len(e1), e1->mode,
				e2->path, tree_entry_len(e2), e2->mode);
	return cmp;
}