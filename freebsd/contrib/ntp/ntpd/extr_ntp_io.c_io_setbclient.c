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
struct interface {int flags; scalar_t__ bfd; scalar_t__ fd; int /*<<< orphan*/  name; int /*<<< orphan*/  ifnum; int /*<<< orphan*/  bcast; int /*<<< orphan*/  family; scalar_t__ ignore_packets; struct interface* elink; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
#define  EADDRINUSE 129 
#define  EADDRNOTAVAIL 128 
 int INT_BCASTOPEN ; 
 int INT_BROADCAST ; 
 int INT_LOOPBACK ; 
 int INT_WILDCARD ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  IS_IPV4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  broadcast_client_enabled ; 
 struct interface* ep_list ; 
 int errno ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ open_socket (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct interface*) ; 
 int /*<<< orphan*/  set_reuseaddr (int) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

void
io_setbclient(void)
{
#ifdef OPEN_BCAST_SOCKET
	struct interface *	interf;
	unsigned int		nif;

	nif = 0;
	set_reuseaddr(1);

	for (interf = ep_list;
	     interf != NULL;
	     interf = interf->elink) {

		if (interf->flags & (INT_WILDCARD | INT_LOOPBACK))
			continue;

		/* use only allowed addresses */
		if (interf->ignore_packets)
			continue;

		/* Need a broadcast-capable interface */
		if (!(interf->flags & INT_BROADCAST))
			continue;

		/* Only IPv4 addresses are valid for broadcast */
		REQUIRE(IS_IPV4(&interf->bcast));

		/* Do we already have the broadcast address open? */
		if (interf->flags & INT_BCASTOPEN) {
			/*
			 * account for already open interfaces to avoid
			 * misleading warning below
			 */
			nif++;
			continue;
		}

		/*
		 * Try to open the broadcast address
		 */
		interf->family = AF_INET;
		interf->bfd = open_socket(&interf->bcast, 1, 0, interf);

		/*
		 * If we succeeded then we use it otherwise enable
		 * broadcast on the interface address
		 */
		if (interf->bfd != INVALID_SOCKET) {
			nif++;
			interf->flags |= INT_BCASTOPEN;
			msyslog(LOG_INFO,
				"Listen for broadcasts to %s on interface #%d %s",
				stoa(&interf->bcast), interf->ifnum, interf->name);
		} else switch (errno) {
			/* Silently ignore EADDRINUSE as we probably
			 * opened the socket already for an address in
			 * the same network */
		case EADDRINUSE:
			/* Some systems cannot bind a socket to a broadcast
			 * address, as that is not a valid host address. */
		case EADDRNOTAVAIL:
#		    ifdef SYS_WINNT	/*TODO: use for other systems, too? */
			/* avoid recurrence here -- if we already have a
			 * regular socket, it's quite useless to try this
			 * again.
			 */
			if (interf->fd != INVALID_SOCKET) {
				interf->flags |= INT_BCASTOPEN;
				nif++;
			}
#		    endif
			break;

		default:
			msyslog(LOG_INFO,
				"failed to listen for broadcasts to %s on interface #%d %s",
				stoa(&interf->bcast), interf->ifnum, interf->name);
			break;
		}
	}
	set_reuseaddr(0);
	if (nif != 0) {
		broadcast_client_enabled = ISC_TRUE;
		DPRINTF(1, ("io_setbclient: listening to %d broadcast addresses\n", nif));
	} else {
		broadcast_client_enabled = ISC_FALSE;
		msyslog(LOG_ERR,
			"Unable to listen for broadcasts, no broadcast interfaces available");
	}
#else
	msyslog(LOG_ERR,
		"io_setbclient: Broadcast Client disabled by build");
#endif	/* OPEN_BCAST_SOCKET */
}