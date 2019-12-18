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
typedef  size_t u_int ;
struct pkt {int /*<<< orphan*/  org; } ;
struct recvbuf {scalar_t__ dstadr; struct pkt recv_pkt; int /*<<< orphan*/  recv_srcadr; } ;
struct peer {scalar_t__ hmode; scalar_t__ dstadr; int /*<<< orphan*/  aorg; int /*<<< orphan*/  srcadr; struct peer* adr_link; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_PORT_EQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int AM_ERR ; 
 int AM_NOMATCH ; 
 int AM_PROCPKT ; 
 int /*<<< orphan*/  L_ISEQU (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MATCH_ASSOC (scalar_t__,int) ; 
 scalar_t__ MODE_BCLIENT ; 
 int MODE_SERVER ; 
 scalar_t__ NO_PEER ; 
 int /*<<< orphan*/  NTOHL_FP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t NTP_HASH_ADDR (int /*<<< orphan*/ *) ; 
 scalar_t__ findmanycastpeer (struct recvbuf*) ; 
 int /*<<< orphan*/  findpeer_calls ; 
 struct peer** peer_hash ; 

struct peer *
findpeer(
	struct recvbuf *rbufp,
	int		pkt_mode,
	int *		action
	)
{
	struct peer *	p;
	sockaddr_u *	srcadr;
	u_int		hash;
	struct pkt *	pkt;
	l_fp		pkt_org;

	findpeer_calls++;
	srcadr = &rbufp->recv_srcadr;
	hash = NTP_HASH_ADDR(srcadr);
	for (p = peer_hash[hash]; p != NULL; p = p->adr_link) {

		/* [Bug 3072] ensure interface of peer matches */
		/* [Bug 3356] ... if NOT a broadcast peer!     */
		if (p->hmode != MODE_BCLIENT && p->dstadr != rbufp->dstadr)
			continue;

		/* ensure peer source address matches */
		if ( ! ADDR_PORT_EQ(srcadr, &p->srcadr))
			continue;
		
		/* If the association matching rules determine that this
		 * is not a valid combination, then look for the next
		 * valid peer association.
		 */
		*action = MATCH_ASSOC(p->hmode, pkt_mode);

		/* A response to our manycastclient solicitation might
		 * be misassociated with an ephemeral peer already spun
		 * for the server.  If the packet's org timestamp
		 * doesn't match the peer's, check if it matches the
		 * ACST prototype peer's.  If so it is a redundant
		 * solicitation response, return AM_ERR to discard it.
		 * [Bug 1762]
		 */
		if (MODE_SERVER == pkt_mode && AM_PROCPKT == *action) {
			pkt = &rbufp->recv_pkt;
			NTOHL_FP(&pkt->org, &pkt_org);
			if (!L_ISEQU(&p->aorg, &pkt_org) &&
			    findmanycastpeer(rbufp))
				*action = AM_ERR;
		}

		/* if an error was returned, exit back right here. */
		if (*action == AM_ERR)
			return NULL;

		/* if a match is found, we stop our search. */
		if (*action != AM_NOMATCH)
			break;
	}

	/* If no matching association is found... */
	if (NULL == p)
		*action = MATCH_ASSOC(NO_PEER, pkt_mode);

	return p;
}