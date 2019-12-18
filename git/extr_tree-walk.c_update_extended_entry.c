#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ path; } ;
struct TYPE_4__ {TYPE_1__ entry; } ;
struct tree_desc_x {struct tree_desc_skip* skip; TYPE_2__ d; } ;
struct tree_desc_skip {scalar_t__ ptr; struct tree_desc_skip* prev; } ;
struct name_entry {scalar_t__ path; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_tree_entry (TYPE_2__*) ; 
 struct tree_desc_skip* xmalloc (int) ; 

__attribute__((used)) static void update_extended_entry(struct tree_desc_x *t, struct name_entry *a)
{
	if (t->d.entry.path == a->path) {
		update_tree_entry(&t->d);
	} else {
		/* we have returned this entry early */
		struct tree_desc_skip *skip = xmalloc(sizeof(*skip));
		skip->ptr = a->path;
		skip->prev = t->skip;
		t->skip = skip;
	}
}