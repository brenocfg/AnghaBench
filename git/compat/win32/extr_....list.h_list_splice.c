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
struct list_head {struct list_head* next; struct list_head* prev; } ;

/* Variables and functions */

__attribute__((used)) static inline void list_splice(struct list_head *add, struct list_head *head)
{
	/* Do nothing if the list which gets added is empty. */
	if (add != add->next) {
		add->next->prev = head;
		add->prev->next = head->next;
		head->next->prev = add->prev;
		head->next = add->next;
	}
}