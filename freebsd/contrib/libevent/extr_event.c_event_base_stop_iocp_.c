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
struct event_base {int /*<<< orphan*/ * iocp; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int event_iocp_shutdown_ (int /*<<< orphan*/ *,int) ; 

void
event_base_stop_iocp_(struct event_base *base)
{
#ifdef _WIN32
	int rv;

	if (!base->iocp)
		return;
	rv = event_iocp_shutdown_(base->iocp, -1);
	EVUTIL_ASSERT(rv >= 0);
	base->iocp = NULL;
#endif
}