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
typedef  int u_char ;
struct peer {int hpoll; scalar_t__ outdate; scalar_t__ timelastrec; int reach; int cast_flags; scalar_t__ unreach; scalar_t__ ttl; scalar_t__ burst; int flags; scalar_t__ retry; scalar_t__ hmode; int /*<<< orphan*/  maxpoll; int /*<<< orphan*/  ppoll; } ;

/* Variables and functions */
 int FLAG_BURST ; 
 int FLAG_CONFIG ; 
 int FLAG_IBURST ; 
 int FLAG_PREEMPT ; 
 scalar_t__ LEAP_NOTINSYNC ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  MAXDISPERSE ; 
 int MDF_ACAST ; 
 int MDF_BCAST ; 
 int MDF_MCAST ; 
 int MDF_POOL ; 
 scalar_t__ MODE_BCLIENT ; 
 void* NTP_RETRY ; 
 scalar_t__ NTP_UNREACH ; 
 int /*<<< orphan*/  PEVNT_RESTART ; 
 int /*<<< orphan*/  PEVNT_UNREACH ; 
 int /*<<< orphan*/  clock_filter (struct peer*,int,int,int /*<<< orphan*/ ) ; 
 void* current_time ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ mode_ntpdate ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msyslog_term ; 
 int peer_associations ; 
 int /*<<< orphan*/  peer_clear (struct peer*,char*) ; 
 scalar_t__ peer_ntpdate ; 
 int /*<<< orphan*/  peer_unfit (struct peer*) ; 
 int /*<<< orphan*/  peer_xmit (struct peer*) ; 
 int /*<<< orphan*/  poll_update (struct peer*,int) ; 
 int /*<<< orphan*/  pool_xmit (struct peer*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  report_event (int /*<<< orphan*/ ,struct peer*,char*) ; 
 scalar_t__ score_all (struct peer*) ; 
 scalar_t__ sys_beacon ; 
 scalar_t__ sys_leap ; 
 int sys_maxclock ; 
 scalar_t__ sys_minclock ; 
 int sys_poll ; 
 scalar_t__ sys_survivors ; 
 scalar_t__ sys_ttlmax ; 
 int /*<<< orphan*/  unpeer (struct peer*) ; 

void
transmit(
	struct peer *peer	/* peer structure pointer */
	)
{
	u_char	hpoll;

	/*
	 * The polling state machine. There are two kinds of machines,
	 * those that never expect a reply (broadcast and manycast
	 * server modes) and those that do (all other modes). The dance
	 * is intricate...
	 */
	hpoll = peer->hpoll;

	/*
	 * If we haven't received anything (even if unsync) since last
	 * send, reset ppoll.
	 */
	if (peer->outdate > peer->timelastrec && !peer->reach)
		peer->ppoll = peer->maxpoll;

	/*
	 * In broadcast mode the poll interval is never changed from
	 * minpoll.
	 */
	if (peer->cast_flags & (MDF_BCAST | MDF_MCAST)) {
		peer->outdate = current_time;
		poll_update(peer, hpoll);
		if (sys_leap != LEAP_NOTINSYNC)
			peer_xmit(peer);
		return;
	}

	/*
	 * In manycast mode we start with unity ttl. The ttl is
	 * increased by one for each poll until either sys_maxclock
	 * servers have been found or the maximum ttl is reached. When
	 * sys_maxclock servers are found we stop polling until one or
	 * more servers have timed out or until less than sys_minclock
	 * associations turn up. In this case additional better servers
	 * are dragged in and preempt the existing ones.  Once every
	 * sys_beacon seconds we are to transmit unconditionally, but
	 * this code is not quite right -- peer->unreach counts polls
	 * and is being compared with sys_beacon, so the beacons happen
	 * every sys_beacon polls.
	 */
	if (peer->cast_flags & MDF_ACAST) {
		peer->outdate = current_time;
		poll_update(peer, hpoll);
		if (peer->unreach > sys_beacon) {
			peer->unreach = 0;
			peer->ttl = 0;
			peer_xmit(peer);
		} else if (   sys_survivors < sys_minclock
			   || peer_associations < sys_maxclock) {
			if (peer->ttl < sys_ttlmax)
				peer->ttl++;
			peer_xmit(peer);
		}
		peer->unreach++;
		return;
	}

	/*
	 * Pool associations transmit unicast solicitations when there
	 * are less than a hard limit of 2 * sys_maxclock associations,
	 * and either less than sys_minclock survivors or less than
	 * sys_maxclock associations.  The hard limit prevents unbounded
	 * growth in associations if the system clock or network quality
	 * result in survivor count dipping below sys_minclock often.
	 * This was observed testing with pool, where sys_maxclock == 12
	 * resulted in 60 associations without the hard limit.  A
	 * similar hard limit on manycastclient ephemeral associations
	 * may be appropriate.
	 */
	if (peer->cast_flags & MDF_POOL) {
		peer->outdate = current_time;
		poll_update(peer, hpoll);
		if (   (peer_associations <= 2 * sys_maxclock)
		    && (   peer_associations < sys_maxclock
			|| sys_survivors < sys_minclock))
			pool_xmit(peer);
		return;
	}

	/*
	 * In unicast modes the dance is much more intricate. It is
	 * designed to back off whenever possible to minimize network
	 * traffic.
	 */
	if (peer->burst == 0) {
		u_char oreach;

		/*
		 * Update the reachability status. If not heard for
		 * three consecutive polls, stuff infinity in the clock
		 * filter.
		 */
		oreach = peer->reach;
		peer->outdate = current_time;
		peer->unreach++;
		peer->reach <<= 1;
		if (!peer->reach) {

			/*
			 * Here the peer is unreachable. If it was
			 * previously reachable raise a trap. Send a
			 * burst if enabled.
			 */
			clock_filter(peer, 0., 0., MAXDISPERSE);
			if (oreach) {
				peer_unfit(peer);
				report_event(PEVNT_UNREACH, peer, NULL);
			}
			if (   (peer->flags & FLAG_IBURST)
			    && peer->retry == 0)
				peer->retry = NTP_RETRY;
		} else {

			/*
			 * Here the peer is reachable. Send a burst if
			 * enabled and the peer is fit.  Reset unreach
			 * for persistent and ephemeral associations.
			 * Unreach is also reset for survivors in
			 * clock_select().
			 */
			hpoll = sys_poll;
			if (!(peer->flags & FLAG_PREEMPT))
				peer->unreach = 0;
			if (   (peer->flags & FLAG_BURST)
			    && peer->retry == 0
			    && !peer_unfit(peer))
				peer->retry = NTP_RETRY;
		}

		/*
		 * Watch for timeout.  If ephemeral, toss the rascal;
		 * otherwise, bump the poll interval. Note the
		 * poll_update() routine will clamp it to maxpoll.
		 * If preemptible and we have more peers than maxclock,
		 * and this peer has the minimum score of preemptibles,
		 * demobilize.
		 */
		if (peer->unreach >= NTP_UNREACH) {
			hpoll++;
			/* ephemeral: no FLAG_CONFIG nor FLAG_PREEMPT */
			if (!(peer->flags & (FLAG_CONFIG | FLAG_PREEMPT))) {
				report_event(PEVNT_RESTART, peer, "timeout");
				peer_clear(peer, "TIME");
				unpeer(peer);
				return;
			}
			if (   (peer->flags & FLAG_PREEMPT)
			    && (peer_associations > sys_maxclock)
			    && score_all(peer)) {
				report_event(PEVNT_RESTART, peer, "timeout");
				peer_clear(peer, "TIME");
				unpeer(peer);
				return;
			}
		}
	} else {
		peer->burst--;
		if (peer->burst == 0) {

			/*
			 * If ntpdate mode and the clock has not been
			 * set and all peers have completed the burst,
			 * we declare a successful failure.
			 */
			if (mode_ntpdate) {
				peer_ntpdate--;
				if (peer_ntpdate == 0) {
					msyslog(LOG_NOTICE,
					    "ntpd: no servers found");
					if (!msyslog_term)
						printf(
						    "ntpd: no servers found\n");
					exit (0);
				}
			}
		}
	}
	if (peer->retry > 0)
		peer->retry--;

	/*
	 * Do not transmit if in broadcast client mode.
	 */
	poll_update(peer, hpoll);
	if (peer->hmode != MODE_BCLIENT)
		peer_xmit(peer);

	return;
}