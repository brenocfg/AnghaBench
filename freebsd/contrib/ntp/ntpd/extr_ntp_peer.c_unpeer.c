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
struct peer {int flags; int /*<<< orphan*/  srcadr; int /*<<< orphan*/  associd; } ;

/* Variables and functions */
 int FLAG_PREEMPT ; 
 int FLAG_REFCLOCK ; 
 int /*<<< orphan*/  PEVNT_DEMOBIL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free_peer (struct peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mprintf_event (int /*<<< orphan*/ ,struct peer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peer_associations ; 
 int /*<<< orphan*/  peer_demobilizations ; 
 int /*<<< orphan*/  peer_preempt ; 
 int /*<<< orphan*/  refclock_unpeer (struct peer*) ; 
 int /*<<< orphan*/  restrict_source (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_peerdstadr (struct peer*,int /*<<< orphan*/ *) ; 

void
unpeer(
	struct peer *peer
	)
{
	mprintf_event(PEVNT_DEMOBIL, peer, "assoc %u", peer->associd);
	restrict_source(&peer->srcadr, 1, 0);
	set_peerdstadr(peer, NULL);
	peer_demobilizations++;
	peer_associations--;
	if (FLAG_PREEMPT & peer->flags)
		peer_preempt--;
#ifdef REFCLOCK
	/*
	 * If this peer is actually a clock, shut it down first
	 */
	if (FLAG_REFCLOCK & peer->flags)
		refclock_unpeer(peer);
#endif

	free_peer(peer, TRUE);
}