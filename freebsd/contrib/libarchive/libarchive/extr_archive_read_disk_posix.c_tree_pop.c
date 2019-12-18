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
struct tree_entry {size_t dirname_length; int /*<<< orphan*/  name; struct tree_entry* next; struct tree_entry* parent; } ;
struct TYPE_2__ {char* s; size_t length; } ;
struct tree {size_t dirname_length; char* basename; TYPE_1__ path; struct tree_entry* stack; struct tree_entry* current; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct tree_entry*) ; 

__attribute__((used)) static void
tree_pop(struct tree *t)
{
	struct tree_entry *te;

	t->path.s[t->dirname_length] = '\0';
	t->path.length = t->dirname_length;
	if (t->stack == t->current && t->current != NULL)
		t->current = t->current->parent;
	te = t->stack;
	t->stack = te->next;
	t->dirname_length = te->dirname_length;
	t->basename = t->path.s + t->dirname_length;
	while (t->basename[0] == '/')
		t->basename++;
	archive_string_free(&te->name);
	free(te);
}