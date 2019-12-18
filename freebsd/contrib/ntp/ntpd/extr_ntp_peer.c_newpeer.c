#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32 ;
typedef  int u_int ;
typedef  scalar_t__ u_char ;
struct peer {scalar_t__ cast_flags; int associd; int flags; scalar_t__ minpoll; scalar_t__ maxpoll; scalar_t__ hpoll; scalar_t__ keyid; int /*<<< orphan*/  ttl; scalar_t__ version; scalar_t__ hmode; int /*<<< orphan*/  srcadr; TYPE_1__* dstadr; void* timereceived; void* timereachable; void* timereset; int /*<<< orphan*/  precision; void* ident; void* hostname; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  scalar_t__ keyid_t ;
struct TYPE_9__ {int /*<<< orphan*/  sin; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ endpt ;

/* Variables and functions */
 TYPE_1__* ANY_INTERFACE_CHOOSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEBUG_REQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int FLAG_PREEMPT ; 
 int FLAG_SKEY ; 
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ ISREFCLOCKADR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LINK_SLIST (int /*<<< orphan*/ ,struct peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ MDF_ACAST ; 
 scalar_t__ MDF_BCAST ; 
 scalar_t__ MDF_BCLNT ; 
 scalar_t__ MDF_MCAST ; 
 scalar_t__ MDF_POOL ; 
 int NTP_HASH_ADDR (int /*<<< orphan*/ *) ; 
 int NTP_HASH_MASK ; 
 scalar_t__ NTP_MAXDPOLL ; 
 scalar_t__ NTP_MAXKEY ; 
 int /*<<< orphan*/  NTP_MAXPOLL ; 
 scalar_t__ NTP_MINDPOLL ; 
 int /*<<< orphan*/  NTP_MINPOLL ; 
 int /*<<< orphan*/  PEVNT_MOBIL ; 
 int /*<<< orphan*/  UNLINK_HEAD_SLIST (struct peer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adr_link ; 
 int /*<<< orphan*/  aid_link ; 
 int /*<<< orphan*/ * assoc_hash ; 
 int /*<<< orphan*/ * assoc_hash_count ; 
 int /*<<< orphan*/  crypto_flags ; 
 scalar_t__ current_association_ID ; 
 void* current_time ; 
 int /*<<< orphan*/  enable_broadcast (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_multicast_if (TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* estrdup (char const*) ; 
 struct peer* findexistingpeer (int /*<<< orphan*/ *,char const*,struct peer*,scalar_t__,scalar_t__,int*) ; 
 TYPE_1__* findinterface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_peer (struct peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getmorepeermem () ; 
 int /*<<< orphan*/  latoa (TYPE_1__*) ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mode_ntpdate ; 
 int /*<<< orphan*/  mprintf_event (int /*<<< orphan*/ ,struct peer*,char*,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  p_link ; 
 int /*<<< orphan*/  peer_associations ; 
 int /*<<< orphan*/  peer_clear (struct peer*,char*) ; 
 int /*<<< orphan*/  peer_free ; 
 scalar_t__ peer_free_count ; 
 int /*<<< orphan*/ * peer_hash ; 
 int /*<<< orphan*/ * peer_hash_count ; 
 int /*<<< orphan*/  peer_list ; 
 int /*<<< orphan*/  peer_ntpdate ; 
 int /*<<< orphan*/  peer_preempt ; 
 int /*<<< orphan*/  refclock_newpeer (struct peer*) ; 
 int /*<<< orphan*/  restrict_source (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * select_peerinterface (struct peer*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  set_peerdstadr (struct peer*,int /*<<< orphan*/ *) ; 
 char const* stoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_precision ; 

struct peer *
newpeer(
	sockaddr_u *	srcadr,
	const char *	hostname,
	endpt *		dstadr,
	int		ippeerlimit,
	u_char		hmode,
	u_char		version,
	u_char		minpoll,
	u_char		maxpoll,
	u_int		flags,
	u_char		cast_flags,
	u_int32		ttl,
	keyid_t		key,
	const char *	ident
	)
{
	struct peer *	peer;
	u_int		hash;
	int		ip_count = 0;


	DEBUG_REQUIRE(srcadr);

#ifdef AUTOKEY
	/*
	 * If Autokey is requested but not configured, complain loudly.
	 */
	if (!crypto_flags) {
		if (key > NTP_MAXKEY) {
			return (NULL);

		} else if (flags & FLAG_SKEY) {
			msyslog(LOG_ERR, "Autokey not configured");
			return (NULL);
		} 
	}
#endif	/* AUTOKEY */

	/*
	 * For now only pool associations have a hostname.
	 */
	INSIST(NULL == hostname || (MDF_POOL & cast_flags));

	/*
	 * First search from the beginning for an association with given
	 * remote address and mode. If an interface is given, search
	 * from there to find the association which matches that
	 * destination. If the given interface is "any", track down the
	 * actual interface, because that's what gets put into the peer
	 * structure.
	 */
	if (dstadr != NULL) {
		peer = findexistingpeer(srcadr, hostname, NULL, hmode,
					cast_flags, &ip_count);
		while (peer != NULL) {
			if (   peer->dstadr == dstadr
			    || (   (MDF_BCLNT & cast_flags)
				&& (MDF_BCLNT & peer->cast_flags)))
				break;

			if (dstadr == ANY_INTERFACE_CHOOSE(srcadr) &&
			    peer->dstadr == findinterface(srcadr))
				break;

			peer = findexistingpeer(srcadr, hostname, peer,
						hmode, cast_flags, &ip_count);
		}
	} else {
		/* no endpt address given */
		peer = findexistingpeer(srcadr, hostname, NULL, hmode,
					cast_flags, &ip_count);
	}

	/*
	 * If a peer is found, this would be a duplicate and we don't
	 * allow that. This avoids duplicate ephemeral (broadcast/
	 * multicast) and preemptible (manycast and pool) client
	 * associations.
	 */
	if (peer != NULL) {
		DPRINTF(2, ("newpeer(%s) found existing association\n",
			(hostname)
			    ? hostname
			    : stoa(srcadr)));
		return NULL;
	}

DPRINTF(1, ("newpeer(%s) found no existing and %d other associations\n",
		(hostname)
		    ? hostname
		    : stoa(srcadr),
		ip_count));

	/* Check ippeerlimit wrt ip_count */
	if (ippeerlimit > -1) {
		if (ip_count + 1 > ippeerlimit) {
			DPRINTF(2, ("newpeer(%s) denied - ippeerlimit %d\n",
				(hostname)
				    ? hostname
				    : stoa(srcadr),
				ippeerlimit));
			return NULL;
		}
	} else {
		DPRINTF(1, ("newpeer(%s) - ippeerlimit %d ignored\n",
			(hostname)
			    ? hostname
			    : stoa(srcadr),
			ippeerlimit));
	}

	/*
	 * Allocate a new peer structure. Some dirt here, since some of
	 * the initialization requires knowlege of our system state.
	 */
	if (peer_free_count == 0)
		getmorepeermem();
	UNLINK_HEAD_SLIST(peer, peer_free, p_link);
	INSIST(peer != NULL);
	peer_free_count--;
	peer_associations++;
	if (FLAG_PREEMPT & flags)
		peer_preempt++;

	/*
	 * Assign an association ID and increment the system variable.
	 */
	peer->associd = current_association_ID;
	if (++current_association_ID == 0)
		++current_association_ID;

	peer->srcadr = *srcadr;
	if (hostname != NULL)
		peer->hostname = estrdup(hostname);
	peer->hmode = hmode;
	peer->version = version;
	peer->flags = flags;
	peer->cast_flags = cast_flags;
	set_peerdstadr(peer, 
		       select_peerinterface(peer, srcadr, dstadr));

	/*
	 * It is an error to set minpoll less than NTP_MINPOLL or to
	 * set maxpoll greater than NTP_MAXPOLL. However, minpoll is
	 * clamped not greater than NTP_MAXPOLL and maxpoll is clamped
	 * not less than NTP_MINPOLL without complaint. Finally,
	 * minpoll is clamped not greater than maxpoll.
	 */
	if (minpoll == 0)
		peer->minpoll = NTP_MINDPOLL;
	else
		peer->minpoll = min(minpoll, NTP_MAXPOLL);
	if (maxpoll == 0)
		peer->maxpoll = NTP_MAXDPOLL;
	else
		peer->maxpoll = max(maxpoll, NTP_MINPOLL);
	if (peer->minpoll > peer->maxpoll)
		peer->minpoll = peer->maxpoll;

	if (peer->dstadr != NULL)
		DPRINTF(3, ("newpeer(%s): using fd %d and our addr %s\n",
			stoa(srcadr), peer->dstadr->fd,
			stoa(&peer->dstadr->sin)));
	else
		DPRINTF(3, ("newpeer(%s): local interface currently not bound\n",
			stoa(srcadr)));	

	/*
	 * Broadcast needs the socket enabled for broadcast
	 */
	if ((MDF_BCAST & cast_flags) && peer->dstadr != NULL)
		enable_broadcast(peer->dstadr, srcadr);

	/*
	 * Multicast needs the socket interface enabled for multicast
	 */
	if ((MDF_MCAST & cast_flags) && peer->dstadr != NULL)
		enable_multicast_if(peer->dstadr, srcadr);

#ifdef AUTOKEY
	if (key > NTP_MAXKEY)
		peer->flags |= FLAG_SKEY;
#endif	/* AUTOKEY */
	peer->ttl = ttl;
	peer->keyid = key;
	if (ident != NULL)
		peer->ident = estrdup(ident);
	peer->precision = sys_precision;
	peer->hpoll = peer->minpoll;
	if (cast_flags & MDF_ACAST)
		peer_clear(peer, "ACST");
	else if (cast_flags & MDF_POOL)
		peer_clear(peer, "POOL");
	else if (cast_flags & MDF_MCAST)
		peer_clear(peer, "MCST");
	else if (cast_flags & MDF_BCAST)
		peer_clear(peer, "BCST");
	else
		peer_clear(peer, "INIT");
	if (mode_ntpdate)
		peer_ntpdate++;

	/*
	 * Note time on statistics timers.
	 */
	peer->timereset = current_time;
	peer->timereachable = current_time;
	peer->timereceived = current_time;

	if (ISREFCLOCKADR(&peer->srcadr)) {
#ifdef REFCLOCK
		/*
		 * We let the reference clock support do clock
		 * dependent initialization.  This includes setting
		 * the peer timer, since the clock may have requirements
		 * for this.
		 */
		if (maxpoll == 0)
			peer->maxpoll = peer->minpoll;
		if (!refclock_newpeer(peer)) {
			/*
			 * Dump it, something screwed up
			 */
			set_peerdstadr(peer, NULL);
			free_peer(peer, 0);
			return NULL;
		}
#else /* REFCLOCK */
		msyslog(LOG_ERR, "refclock %s isn't supported. ntpd was compiled without refclock support.",
			stoa(&peer->srcadr));
		set_peerdstadr(peer, NULL);
		free_peer(peer, 0);
		return NULL;
#endif /* REFCLOCK */
	}

	/*
	 * Put the new peer in the hash tables.
	 */
	hash = NTP_HASH_ADDR(&peer->srcadr);
	LINK_SLIST(peer_hash[hash], peer, adr_link);
	peer_hash_count[hash]++;
	hash = peer->associd & NTP_HASH_MASK;
	LINK_SLIST(assoc_hash[hash], peer, aid_link);
	assoc_hash_count[hash]++;
	LINK_SLIST(peer_list, peer, p_link);

	restrict_source(&peer->srcadr, 0, 0);
	mprintf_event(PEVNT_MOBIL, peer, "assoc %d", peer->associd);
	DPRINTF(1, ("newpeer: %s->%s mode %u vers %u poll %u %u flags 0x%x 0x%x ttl %u key %08x\n",
	    latoa(peer->dstadr), stoa(&peer->srcadr), peer->hmode,
	    peer->version, peer->minpoll, peer->maxpoll, peer->flags,
	    peer->cast_flags, peer->ttl, peer->keyid));
	return peer;
}