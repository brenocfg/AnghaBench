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
struct volatile_list_head {struct volatile_list_head volatile* next; struct volatile_list_head volatile* prev; } ;

/* Variables and functions */

__attribute__((used)) static inline void volatile_list_add(volatile struct volatile_list_head *newp,
				     volatile struct volatile_list_head *head)
{
	head->next->prev = newp;
	newp->next = head->next;
	newp->prev = head;
	head->next = newp;
}