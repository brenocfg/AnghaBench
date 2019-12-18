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
typedef  int /*<<< orphan*/  u_short ;
struct interface {scalar_t__ fd; int flags; scalar_t__ bfd; scalar_t__ family; int /*<<< orphan*/  sin; int /*<<< orphan*/  ignore_packets; int /*<<< orphan*/  ifnum; int /*<<< orphan*/  name; int /*<<< orphan*/  bcast; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_3__ {int /*<<< orphan*/  addr; struct TYPE_3__* link; } ;
typedef  TYPE_1__ remaddr_t ;
typedef  struct interface endpt ;

/* Variables and functions */
 scalar_t__ AF (int /*<<< orphan*/ *) ; 
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  DPRINT_INTERFACE (int,struct interface*) ; 
 int INT_BROADCAST ; 
 int INT_LOOPBACK ; 
 int INT_MULTICAST ; 
 int INT_WILDCARD ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IS_MCAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int RESM_INTERFACE ; 
 int RESM_NTPONLY ; 
 int /*<<< orphan*/  RESTRICT_FLAGS ; 
 int /*<<< orphan*/  RES_IGNORE ; 
 int /*<<< orphan*/  SET_HOSTMASK (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  add_addr_to_list (int /*<<< orphan*/ *,struct interface*) ; 
 int /*<<< orphan*/  add_interface (struct interface*) ; 
 int /*<<< orphan*/  delete_interface (struct interface*) ; 
 int /*<<< orphan*/  hack_restrict (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_listen_address (struct interface*) ; 
 struct interface* loopback_interface ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct interface* new_interface (struct interface*) ; 
 scalar_t__ open_socket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct interface*) ; 
 TYPE_1__* remoteaddr_list ; 
 scalar_t__ socket_multicast_enable (struct interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct interface *
create_interface(
	u_short			port,
	struct interface *	protot
	)
{
	sockaddr_u	resmask;
	endpt *		iface;
#if defined(MCAST) && defined(MULTICAST_NONEWSOCKET)
	remaddr_t *	entry;
	remaddr_t *	next_entry;
#endif
	DPRINTF(2, ("create_interface(%s#%d)\n", stoa(&protot->sin),
		    port));

	/* build an interface */
	iface = new_interface(protot);

	/*
	 * create socket
	 */
	iface->fd = open_socket(&iface->sin, 0, 0, iface);

	if (iface->fd != INVALID_SOCKET)
		log_listen_address(iface);

	if ((INT_BROADCAST & iface->flags)
	    && iface->bfd != INVALID_SOCKET)
		msyslog(LOG_INFO, "Listening on broadcast address %s#%d",
			stoa((&iface->bcast)), port);

	if (INVALID_SOCKET == iface->fd
	    && INVALID_SOCKET == iface->bfd) {
		msyslog(LOG_ERR, "unable to create socket on %s (%d) for %s#%d",
			iface->name,
			iface->ifnum,
			stoa((&iface->sin)),
			port);
		delete_interface(iface);
		return NULL;
	}

	/*
	 * Blacklist our own addresses, no use talking to ourself
	 */
	SET_HOSTMASK(&resmask, AF(&iface->sin));
	hack_restrict(RESTRICT_FLAGS, &iface->sin, &resmask,
		      -4, RESM_NTPONLY | RESM_INTERFACE, RES_IGNORE, 0);

	/*
	 * set globals with the first found
	 * loopback interface of the appropriate class
	 */
	if (NULL == loopback_interface && AF_INET == iface->family
	    && (INT_LOOPBACK & iface->flags))
		loopback_interface = iface;

	/*
	 * put into our interface list
	 */
	add_addr_to_list(&iface->sin, iface);
	add_interface(iface);

#if defined(MCAST) && defined(MULTICAST_NONEWSOCKET)
	/*
	 * Join any previously-configured compatible multicast groups.
	 */
	if (INT_MULTICAST & iface->flags &&
	    !((INT_LOOPBACK | INT_WILDCARD) & iface->flags) &&
	    !iface->ignore_packets) {
		for (entry = remoteaddr_list;
		     entry != NULL;
		     entry = next_entry) {
			next_entry = entry->link;
			if (AF(&iface->sin) != AF(&entry->addr) ||
			    !IS_MCAST(&entry->addr))
				continue;
			if (socket_multicast_enable(iface,
						    &entry->addr))
				msyslog(LOG_INFO,
					"Joined %s socket to multicast group %s",
					stoa(&iface->sin),
					stoa(&entry->addr));
			else
				msyslog(LOG_ERR,
					"Failed to join %s socket to multicast group %s",
					stoa(&iface->sin),
					stoa(&entry->addr));
		}
	}
#endif	/* MCAST && MCAST_NONEWSOCKET */

	DPRINT_INTERFACE(2, (iface, "created ", "\n"));
	return iface;
}