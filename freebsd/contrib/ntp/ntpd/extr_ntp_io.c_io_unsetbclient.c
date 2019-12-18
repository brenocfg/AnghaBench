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
struct TYPE_4__ {int flags; scalar_t__ bfd; int /*<<< orphan*/  name; int /*<<< orphan*/  ifnum; int /*<<< orphan*/  bcast; struct TYPE_4__* elink; } ;
typedef  TYPE_1__ endpt ;

/* Variables and functions */
 int INT_BCASTOPEN ; 
 int INT_WILDCARD ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  broadcast_client_enabled ; 
 int /*<<< orphan*/  close_and_delete_fd_from_list (scalar_t__) ; 
 TYPE_1__* ep_list ; 
 int /*<<< orphan*/  io_completion_port_remove_socket (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

void
io_unsetbclient(void)
{
	endpt *ep;

	for (ep = ep_list; ep != NULL; ep = ep->elink) {
		if (INT_WILDCARD & ep->flags)
			continue;
		if (!(INT_BCASTOPEN & ep->flags))
			continue;

		if (ep->bfd != INVALID_SOCKET) {
			/* destroy broadcast listening socket */
			msyslog(LOG_INFO,
				"stop listening for broadcasts to %s on interface #%d %s",
				stoa(&ep->bcast), ep->ifnum, ep->name);
#		    ifdef HAVE_IO_COMPLETION_PORT
			io_completion_port_remove_socket(ep->bfd, ep);
#		    endif
			close_and_delete_fd_from_list(ep->bfd);
			ep->bfd = INVALID_SOCKET;
		}
		ep->flags &= ~INT_BCASTOPEN;
	}
	broadcast_client_enabled = ISC_FALSE;
}