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
struct serviced_query {struct service_callback* cblist; } ;
struct service_callback {void* cb_arg; struct service_callback* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct service_callback*) ; 

__attribute__((used)) static void
callback_list_remove(struct serviced_query* sq, void* cb_arg)
{
	struct service_callback** pp = &sq->cblist;
	while(*pp) {
		if((*pp)->cb_arg == cb_arg) {
			struct service_callback* del = *pp;
			*pp = del->next;
			free(del);
			return;
		}
		pp = &(*pp)->next;
	}
}