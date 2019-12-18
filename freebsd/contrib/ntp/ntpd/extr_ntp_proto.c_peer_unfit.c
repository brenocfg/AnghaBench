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
struct peer {scalar_t__ leap; int stratum; int flags; int flash; int /*<<< orphan*/  reach; int /*<<< orphan*/  hpoll; } ;

/* Variables and functions */
 int FLAG_NOSELECT ; 
 int FLAG_REFCLOCK ; 
 scalar_t__ LEAP_NOTINSYNC ; 
 int PEER_TEST_MASK ; 
 int TEST10 ; 
 int TEST11 ; 
 int TEST12 ; 
 int TEST13 ; 
 int ULOGTOD (int /*<<< orphan*/ ) ; 
 int clock_phi ; 
 scalar_t__ local_refid (struct peer*) ; 
 scalar_t__ root_distance (struct peer*) ; 
 int sys_ceiling ; 
 int sys_floor ; 
 scalar_t__ sys_maxdist ; 

int				/* FALSE if fit, TRUE if unfit */
peer_unfit(
	struct peer *peer	/* peer structure pointer */
	)
{
	int	rval = 0;

	/*
	 * A stratum error occurs if (1) the server has never been
	 * synchronized, (2) the server stratum is below the floor or
	 * greater than or equal to the ceiling.
	 */
	if (   peer->leap == LEAP_NOTINSYNC
	    || peer->stratum < sys_floor
	    || peer->stratum >= sys_ceiling) {
		rval |= TEST10;		/* bad synch or stratum */
	}

	/*
	 * A distance error for a remote peer occurs if the root
	 * distance is greater than or equal to the distance threshold
	 * plus the increment due to one host poll interval.
	 */
	if (   !(peer->flags & FLAG_REFCLOCK)
	    && root_distance(peer) >= sys_maxdist
				      + clock_phi * ULOGTOD(peer->hpoll)) {
		rval |= TEST11;		/* distance exceeded */
	}

	/*
	 * A loop error occurs if the remote peer is synchronized to the
	 * local peer or if the remote peer is synchronized to the same
	 * server as the local peer but only if the remote peer is
	 * neither a reference clock nor an orphan.
	 */
	if (peer->stratum > 1 && local_refid(peer)) {
		rval |= TEST12;		/* synchronization loop */
	}

	/*
	 * An unreachable error occurs if the server is unreachable or
	 * the noselect bit is set.
	 */
	if (!peer->reach || (peer->flags & FLAG_NOSELECT)) {
		rval |= TEST13;		/* unreachable */
	}

	peer->flash &= ~PEER_TEST_MASK;
	peer->flash |= rval;
	return (rval);
}