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

__attribute__((used)) static inline void list_add_tail(struct list_head *newp, struct list_head *head)
{
	head->prev->next = newp;
	newp->next = head;
	newp->prev = head->prev;
	head->prev = newp;
}