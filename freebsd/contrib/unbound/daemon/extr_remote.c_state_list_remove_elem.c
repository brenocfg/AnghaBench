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
struct rc_state {struct rc_state* next; struct comm_point* c; } ;
struct comm_point {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
state_list_remove_elem(struct rc_state** list, struct comm_point* c)
{
	while(*list) {
		if( (*list)->c == c) {
			*list = (*list)->next;
			return;
		}
		list = &(*list)->next;
	}
}