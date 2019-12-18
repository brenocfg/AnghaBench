#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  event; scalar_t__ armed; } ;
typedef  TYPE_1__ REMOTE_EVENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  _sema_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
remote_event_create(REMOTE_EVENT_T *event)
{
	event->armed = 0;
	/* Don't clear the 'fired' flag because it may already have been set
	** by the other side. */
	_sema_init(event->event, 0);
}