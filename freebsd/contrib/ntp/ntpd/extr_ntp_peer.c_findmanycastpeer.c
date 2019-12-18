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
struct pkt {int /*<<< orphan*/  org; } ;
struct recvbuf {struct pkt recv_pkt; } ;
struct peer {int cast_flags; int /*<<< orphan*/  aorg; struct peer* p_link; } ;
typedef  int /*<<< orphan*/  l_fp ;

/* Variables and functions */
 scalar_t__ L_ISEQU (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MDF_SOLICIT_MASK ; 
 int /*<<< orphan*/  NTOHL_FP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct peer* peer_list ; 

struct peer *
findmanycastpeer(
	struct recvbuf *rbufp	/* receive buffer pointer */
	)
{
	struct peer *peer;
	struct pkt *pkt;
	l_fp p_org;

 	/*
 	 * This routine is called upon arrival of a server-mode response
	 * to a manycastclient multicast solicitation, or to a pool
	 * server unicast solicitation.  Search the peer list for a
	 * manycastclient association where the last transmit timestamp
	 * matches the response packet's originate timestamp.  There can
	 * be multiple manycastclient associations, or multiple pool
	 * solicitation assocations, so this assumes the transmit
	 * timestamps are unique for such.
	 */
	pkt = &rbufp->recv_pkt;
	for (peer = peer_list; peer != NULL; peer = peer->p_link)
		if (MDF_SOLICIT_MASK & peer->cast_flags) {
			NTOHL_FP(&pkt->org, &p_org);
			if (L_ISEQU(&p_org, &peer->aorg))
				break;
		}

	return peer;
}