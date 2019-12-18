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
struct ub_event {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ev; } ;

/* Variables and functions */
 TYPE_1__* AS_MY_EVENT (struct ub_event*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  winsock_unregister_wsaevent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
my_winsock_unregister_wsaevent(struct ub_event* ev)
{
#if defined(USE_MINI_EVENT) && defined(USE_WINSOCK)
	winsock_unregister_wsaevent(&AS_MY_EVENT(ev)->ev);
	free(AS_MY_EVENT(ev));
#else
	(void)ev;
#endif
}