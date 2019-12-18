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
struct comm_base {struct comm_base* eb; int /*<<< orphan*/ * base; int /*<<< orphan*/  slow_accept; scalar_t__ slow_accept_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct comm_base*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ ub_event_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_event_free (int /*<<< orphan*/ ) ; 

void 
comm_base_delete_no_base(struct comm_base* b)
{
	if(!b)
		return;
	if(b->eb->slow_accept_enabled) {
		if(ub_event_del(b->eb->slow_accept) != 0) {
			log_err("could not event_del slow_accept");
		}
		ub_event_free(b->eb->slow_accept);
	}
	b->eb->base = NULL;
	free(b->eb);
	free(b);
}