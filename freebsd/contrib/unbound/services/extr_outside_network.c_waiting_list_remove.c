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
struct waiting_tcp {struct waiting_tcp* next_waiting; } ;
struct outside_network {struct waiting_tcp* tcp_wait_last; struct waiting_tcp* tcp_wait_first; } ;

/* Variables and functions */

__attribute__((used)) static void
waiting_list_remove(struct outside_network* outnet, struct waiting_tcp* w)
{
	struct waiting_tcp* p = outnet->tcp_wait_first, *prev = NULL;
	while(p) {
		if(p == w) {
			/* remove w */
			if(prev)
				prev->next_waiting = w->next_waiting;
			else	outnet->tcp_wait_first = w->next_waiting;
			if(outnet->tcp_wait_last == w)
				outnet->tcp_wait_last = prev;
			return;
		}
		prev = p;
		p = p->next_waiting;
	}
}