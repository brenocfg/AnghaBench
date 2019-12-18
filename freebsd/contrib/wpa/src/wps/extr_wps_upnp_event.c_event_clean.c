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
struct wps_event_ {int /*<<< orphan*/ * http_event; TYPE_1__* s; } ;
struct TYPE_2__ {struct wps_event_* current_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  http_client_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void event_clean(struct wps_event_ *e)
{
	if (e->s->current_event == e)
		e->s->current_event = NULL;
	http_client_free(e->http_event);
	e->http_event = NULL;
}