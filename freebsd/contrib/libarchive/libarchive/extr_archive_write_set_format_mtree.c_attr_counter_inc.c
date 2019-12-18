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
struct attr_counter {scalar_t__ count; struct attr_counter* next; struct attr_counter* prev; } ;

/* Variables and functions */
 struct attr_counter* attr_counter_new (struct mtree_entry*,struct attr_counter*) ; 

__attribute__((used)) static int
attr_counter_inc(struct attr_counter **top, struct attr_counter *ac,
    struct attr_counter *last, struct mtree_entry *me)
{
	struct attr_counter *pac;

	if (ac != NULL) {
		ac->count++;
		if (*top == ac || ac->prev->count >= ac->count)
			return (0);
		for (pac = ac->prev; pac; pac = pac->prev) {
			if (pac->count >= ac->count)
				break;
		}
		ac->prev->next = ac->next;
		if (ac->next != NULL)
			ac->next->prev = ac->prev;
		if (pac != NULL) {
			ac->prev = pac;
			ac->next = pac->next;
			pac->next = ac;
			if (ac->next != NULL)
				ac->next->prev = ac;
		} else {
			ac->prev = NULL;
			ac->next = *top;
			*top = ac;
			ac->next->prev = ac;
		}
	} else if (last != NULL) {
		ac = attr_counter_new(me, last);
		if (ac == NULL)
			return (-1);
		last->next = ac;
	}
	return (0);
}