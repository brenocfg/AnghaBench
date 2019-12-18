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
struct eloop_event {scalar_t__ event; int /*<<< orphan*/  handler; void* user_data; void* eloop_data; } ;
typedef  int /*<<< orphan*/  eloop_event_handler ;
struct TYPE_2__ {int event_count; struct eloop_event* events; } ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ INVALID_HANDLE_VALUE ; 
 TYPE_1__ eloop ; 
 scalar_t__ eloop_prepare_handles () ; 
 struct eloop_event* os_realloc_array (struct eloop_event*,int,int) ; 

int eloop_register_event(void *event, size_t event_size,
			 eloop_event_handler handler,
			 void *eloop_data, void *user_data)
{
	struct eloop_event *tmp;
	HANDLE h = event;

	if (event_size != sizeof(HANDLE) || h == INVALID_HANDLE_VALUE)
		return -1;

	if (eloop_prepare_handles())
		return -1;

	tmp = os_realloc_array(eloop.events, eloop.event_count + 1,
			       sizeof(struct eloop_event));
	if (tmp == NULL)
		return -1;

	tmp[eloop.event_count].eloop_data = eloop_data;
	tmp[eloop.event_count].user_data = user_data;
	tmp[eloop.event_count].handler = handler;
	tmp[eloop.event_count].event = h;
	eloop.event_count++;
	eloop.events = tmp;

	return 0;
}