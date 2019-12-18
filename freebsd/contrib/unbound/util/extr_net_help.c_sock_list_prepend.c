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
struct sock_list {struct sock_list* next; } ;

/* Variables and functions */

void sock_list_prepend(struct sock_list** list, struct sock_list* add)
{
	struct sock_list* last = add;
	if(!last) 
		return;
	while(last->next)
		last = last->next;
	last->next = *list;
	*list = add;
}