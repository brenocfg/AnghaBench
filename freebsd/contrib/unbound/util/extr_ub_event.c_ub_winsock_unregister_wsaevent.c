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
struct ub_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_EVENT (struct ub_event*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winsock_unregister_wsaevent (int /*<<< orphan*/ ) ; 

void
ub_winsock_unregister_wsaevent(struct ub_event* ev)
{
#if defined(USE_MINI_EVENT) && defined(USE_WINSOCK)
	winsock_unregister_wsaevent(AS_EVENT(ev));
	free(AS_EVENT(ev));
#else
	(void)ev;
#endif
}