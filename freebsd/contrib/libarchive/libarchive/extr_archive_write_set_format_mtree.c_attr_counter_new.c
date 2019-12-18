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
struct mtree_entry {int dummy; } ;
struct attr_counter {int count; struct mtree_entry* m_entry; int /*<<< orphan*/ * next; struct attr_counter* prev; } ;

/* Variables and functions */
 struct attr_counter* malloc (int) ; 

__attribute__((used)) static struct attr_counter *
attr_counter_new(struct mtree_entry *me, struct attr_counter *prev)
{
	struct attr_counter *ac;

	ac = malloc(sizeof(*ac));
	if (ac != NULL) {
		ac->prev = prev;
		ac->next = NULL;
		ac->count = 1;
		ac->m_entry = me;
	}
	return (ac);
}