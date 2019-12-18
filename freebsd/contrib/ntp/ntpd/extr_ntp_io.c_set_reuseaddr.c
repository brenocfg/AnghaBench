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
typedef  int /*<<< orphan*/  flag ;
struct TYPE_3__ {int flags; scalar_t__ fd; int /*<<< orphan*/  sin; int /*<<< orphan*/  name; struct TYPE_3__* elink; } ;
typedef  TYPE_1__ endpt ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int INT_WILDCARD ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 TYPE_1__* ep_list ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_reuseaddr(
	int flag
	)
{
#ifndef SO_EXCLUSIVEADDRUSE
	endpt *ep;

	for (ep = ep_list; ep != NULL; ep = ep->elink) {
		if (ep->flags & INT_WILDCARD)
			continue;

		/*
		 * if ep->fd  is INVALID_SOCKET, we might have a adapter
		 * configured but not present
		 */
		DPRINTF(4, ("setting SO_REUSEADDR on %.16s@%s to %s\n",
			    ep->name, stoa(&ep->sin),
			    flag ? "on" : "off"));

		if (ep->fd != INVALID_SOCKET) {
			if (setsockopt(ep->fd, SOL_SOCKET, SO_REUSEADDR,
				       (void *)&flag, sizeof(flag))) {
				msyslog(LOG_ERR, "set_reuseaddr: setsockopt(%s, SO_REUSEADDR, %s) failed: %m",
					stoa(&ep->sin), flag ? "on" : "off");
			}
		}
	}
#endif /* ! SO_EXCLUSIVEADDRUSE */
}