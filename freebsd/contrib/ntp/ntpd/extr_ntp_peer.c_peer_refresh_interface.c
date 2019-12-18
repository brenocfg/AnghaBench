#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct peer {int cast_flags; scalar_t__ pmode; int /*<<< orphan*/  srcadr; TYPE_1__* dstadr; int /*<<< orphan*/  keyid; int /*<<< orphan*/  ttl; int /*<<< orphan*/  flags; int /*<<< orphan*/  maxpoll; int /*<<< orphan*/  minpoll; int /*<<< orphan*/  version; int /*<<< orphan*/  hmode; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  bcast; int /*<<< orphan*/  sin; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  name; int /*<<< orphan*/  bfd; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ endpt ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int INT_BROADCAST ; 
 int MDF_ACAST ; 
 int MDF_BCAST ; 
 int MDF_MCAST ; 
 scalar_t__ MODE_BROADCAST ; 
 int /*<<< orphan*/  enable_broadcast (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_multicast_if (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  peer_clear (struct peer*,char*) ; 
 TYPE_1__* select_peerinterface (struct peer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_peerdstadr (struct peer*,TYPE_1__*) ; 
 char* stoa (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
peer_refresh_interface(
	struct peer *p
	)
{
	endpt *	niface;
	endpt *	piface;

	niface = select_peerinterface(p, &p->srcadr, NULL);

	DPRINTF(4, (
	    "peer_refresh_interface: %s->%s mode %d vers %d poll %d %d flags 0x%x 0x%x ttl %u key %08x: new interface: ",
	    p->dstadr == NULL ? "<null>" :
	    stoa(&p->dstadr->sin), stoa(&p->srcadr), p->hmode,
	    p->version, p->minpoll, p->maxpoll, p->flags, p->cast_flags,
	    p->ttl, p->keyid));
	if (niface != NULL) {
		DPRINTF(4, (
		    "fd=%d, bfd=%d, name=%.16s, flags=0x%x, ifindex=%u, sin=%s",
		    niface->fd,  niface->bfd, niface->name,
		    niface->flags, niface->ifindex,
		    stoa(&niface->sin)));
		if (niface->flags & INT_BROADCAST)
			DPRINTF(4, (", bcast=%s",
				stoa(&niface->bcast)));
		DPRINTF(4, (", mask=%s\n", stoa(&niface->mask)));
	} else {
		DPRINTF(4, ("<NONE>\n"));
	}

	piface = p->dstadr;
	set_peerdstadr(p, niface);
	if (p->dstadr != NULL) {
		/*
		 * clear crypto if we change the local address
		 */
		if (p->dstadr != piface && !(MDF_ACAST & p->cast_flags)
		    && MODE_BROADCAST != p->pmode)
			peer_clear(p, "XFAC");

		/*
	 	 * Broadcast needs the socket enabled for broadcast
	 	 */
		if (MDF_BCAST & p->cast_flags)
			enable_broadcast(p->dstadr, &p->srcadr);

		/*
	 	 * Multicast needs the socket interface enabled for
		 * multicast
	 	 */
		if (MDF_MCAST & p->cast_flags)
			enable_multicast_if(p->dstadr, &p->srcadr);
	}
}