#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_char ;
struct peer {int hpoll; int minpoll; scalar_t__ hmode; int flags; int flip; size_t* filter_order; int nextdate; int update; int outdate; int /*<<< orphan*/  associd; void* refresh; TYPE_1__* procptr; int /*<<< orphan*/  refid; int /*<<< orphan*/  stratum; int /*<<< orphan*/  leap; void** filter_disp; int /*<<< orphan*/  bxmt; int /*<<< orphan*/  jitter; int /*<<< orphan*/  flash; void* disp; int /*<<< orphan*/  maxpoll; int /*<<< orphan*/  ppoll; int /*<<< orphan*/ * issuer; int /*<<< orphan*/ * subject; int /*<<< orphan*/ * cmmd; int /*<<< orphan*/  sndval; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  recval; int /*<<< orphan*/  cookval; int /*<<< orphan*/ * iffval; } ;
typedef  int /*<<< orphan*/  l_fp ;
struct TYPE_2__ {scalar_t__ coderecv; scalar_t__ codeproc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLEAR_TO_ZERO (struct peer*) ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int FLAG_REFCLOCK ; 
 int FLAG_XLEAVE ; 
 int /*<<< orphan*/  LEAP_NOTINSYNC ; 
 int /*<<< orphan*/  LEN_CLEAR_TO_ZERO (struct peer*) ; 
 int /*<<< orphan*/  LOGTOD (int /*<<< orphan*/ ) ; 
 void* MAXDISPERSE ; 
 scalar_t__ MODE_BCLIENT ; 
 scalar_t__ MODE_PASSIVE ; 
 int NTP_REFRESH ; 
 size_t NTP_SHIFT ; 
 int /*<<< orphan*/  STRATUM_UNSPEC ; 
 void* current_time ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ initializing ; 
 int /*<<< orphan*/  key_expire (struct peer*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ntp_minpkt ; 
 int ntp_random () ; 
 scalar_t__ peer_associations ; 
 int /*<<< orphan*/  peer_unfit (struct peer*) ; 
 int /*<<< orphan*/  sys_precision ; 
 int /*<<< orphan*/  value_free (int /*<<< orphan*/ *) ; 

void
peer_clear(
	struct peer *peer,		/* peer structure */
	const char *ident		/* tally lights */
	)
{
	u_char	u;
	l_fp	bxmt = peer->bxmt;	/* bcast clients retain this! */

#ifdef AUTOKEY
	/*
	 * If cryptographic credentials have been acquired, toss them to
	 * Valhalla. Note that autokeys are ephemeral, in that they are
	 * tossed immediately upon use. Therefore, the keylist can be
	 * purged anytime without needing to preserve random keys. Note
	 * that, if the peer is purged, the cryptographic variables are
	 * purged, too. This makes it much harder to sneak in some
	 * unauthenticated data in the clock filter.
	 */
	key_expire(peer);
	if (peer->iffval != NULL)
		BN_free(peer->iffval);
	value_free(&peer->cookval);
	value_free(&peer->recval);
	value_free(&peer->encrypt);
	value_free(&peer->sndval);
	if (peer->cmmd != NULL)
		free(peer->cmmd);
	if (peer->subject != NULL)
		free(peer->subject);
	if (peer->issuer != NULL)
		free(peer->issuer);
#endif /* AUTOKEY */

	/*
	 * Clear all values, including the optional crypto values above.
	 */
	memset(CLEAR_TO_ZERO(peer), 0, LEN_CLEAR_TO_ZERO(peer));
	peer->ppoll = peer->maxpoll;
	peer->hpoll = peer->minpoll;
	peer->disp = MAXDISPERSE;
	peer->flash = peer_unfit(peer);
	peer->jitter = LOGTOD(sys_precision);

	/* Don't throw away our broadcast replay protection */
	if (peer->hmode == MODE_BCLIENT)
		peer->bxmt = bxmt;

	/*
	 * If interleave mode, initialize the alternate origin switch.
	 */
	if (peer->flags & FLAG_XLEAVE)
		peer->flip = 1;
	for (u = 0; u < NTP_SHIFT; u++) {
		peer->filter_order[u] = u;
		peer->filter_disp[u] = MAXDISPERSE;
	}
#ifdef REFCLOCK
	if (!(peer->flags & FLAG_REFCLOCK)) {
#endif
		peer->leap = LEAP_NOTINSYNC;
		peer->stratum = STRATUM_UNSPEC;
		memcpy(&peer->refid, ident, 4);
#ifdef REFCLOCK
	} else {
		/* Clear refclock sample filter */
		peer->procptr->codeproc = 0;
		peer->procptr->coderecv = 0;
	}
#endif

	/*
	 * During initialization use the association count to spread out
	 * the polls at one-second intervals. Passive associations'
	 * first poll is delayed by the "discard minimum" to avoid rate
	 * limiting. Other post-startup new or cleared associations
	 * randomize the first poll over the minimum poll interval to
	 * avoid implosion.
	 */
	peer->nextdate = peer->update = peer->outdate = current_time;
	if (initializing) {
		peer->nextdate += peer_associations;
	} else if (MODE_PASSIVE == peer->hmode) {
		peer->nextdate += ntp_minpkt;
	} else {
		peer->nextdate += ntp_random() % peer->minpoll;
	}
#ifdef AUTOKEY
	peer->refresh = current_time + (1 << NTP_REFRESH);
#endif	/* AUTOKEY */
	DPRINTF(1, ("peer_clear: at %ld next %ld associd %d refid %s\n",
		    current_time, peer->nextdate, peer->associd,
		    ident));
}