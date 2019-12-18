#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* ev_destroy ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ isc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void
isc_event_free(isc_event_t **eventp) {
	isc_event_t *event;

	REQUIRE(eventp != NULL);
	event = *eventp;
	REQUIRE(event != NULL);

	if (event->ev_destroy != NULL)
		(event->ev_destroy)(event);

	*eventp = NULL;
}