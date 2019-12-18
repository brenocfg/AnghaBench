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
struct list_head {struct list_head* prev; struct list_head* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST (struct list_head*) ; 

__attribute__((used)) static inline void __list_delete(struct list_head *list)
{
	struct list_head *prev, *next;
	prev = list->prev;
	next = list->next;
	prev->next = next;
	next->prev = prev;
	INIT_LIST(list);
}