#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct event_cmd {TYPE_1__* op; struct event_cmd* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (struct event_cmd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct event_cmd*) ; 
 int /*<<< orphan*/  stub1 (struct event_cmd*) ; 

void
free_event_cmd_list(struct event_cmd *p)
{
	struct event_cmd * q;
	for ( ; p ; p = q) {
		q = p->next;
		if (p->op->free)
			p->op->free(p);
		free(p);
	}
}