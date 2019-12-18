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
typedef  int /*<<< orphan*/  u_int32 ;
typedef  scalar_t__ u_char ;
struct pkt {int /*<<< orphan*/  org; } ;
struct recvbuf {int recv_length; struct pkt recv_pkt; } ;
struct peer {int flags; scalar_t__ flip; int /*<<< orphan*/  const aorg; int /*<<< orphan*/  const borg; int /*<<< orphan*/  keyid; } ;
typedef  int /*<<< orphan*/  nak_code ;
typedef  int /*<<< orphan*/  const l_fp ;

/* Variables and functions */
 int FLAG_SKEY ; 
 int /*<<< orphan*/  INVALIDNAK ; 
 int /*<<< orphan*/  L_ISEQU (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ L_ISZERO (int /*<<< orphan*/  const*) ; 
 int MIN_V4_PKT_LEN ; 
 scalar_t__ MODE_ACTIVE ; 
 scalar_t__ MODE_PASSIVE ; 
 scalar_t__ MODE_SERVER ; 
 int /*<<< orphan*/  NONAK ; 
 int /*<<< orphan*/  NTOHL_FP (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VALIDNAK ; 
 int ntohl (int /*<<< orphan*/ ) ; 

nak_code
valid_NAK(
	  struct peer *peer,
	  struct recvbuf *rbufp,
	  u_char hismode
	  )
{
	int		base_packet_length = MIN_V4_PKT_LEN;
	int		remainder_size;
	struct pkt *	rpkt;
	int		keyid;
	l_fp		p_org;	/* origin timestamp */
	const l_fp *	myorg;	/* selected peer origin */

	/*
	 * Check to see if there is something beyond the basic packet
	 */
	if (rbufp->recv_length == base_packet_length) {
		return NONAK;
	}

	remainder_size = rbufp->recv_length - base_packet_length;
	/*
	 * Is this a potential NAK?
	 */
	if (remainder_size != 4) {
		return NONAK;
	}

	/*
	 * Only server responses can contain NAK's
	 */

	if (hismode != MODE_SERVER &&
	    hismode != MODE_ACTIVE &&
	    hismode != MODE_PASSIVE
	    ) {
		return INVALIDNAK;
	}

	/*
	 * Make sure that the extra field in the packet is all zeros
	 */
	rpkt = &rbufp->recv_pkt;
	keyid = ntohl(((u_int32 *)rpkt)[base_packet_length / 4]);
	if (keyid != 0) {
		return INVALIDNAK;
	}

	/*
	 * During the first few packets of the autokey dance there will
	 * not (yet) be a keyid, but in this case FLAG_SKEY is set.
	 * So the NAK is invalid if either there's no peer, or
	 * if the keyid is 0 and FLAG_SKEY is not set.
	 */
	if (!peer || (!peer->keyid && !(peer->flags & FLAG_SKEY))) {
		return INVALIDNAK;
	}

	/*
	 * The ORIGIN must match, or this cannot be a valid NAK, either.
	 */
	NTOHL_FP(&rpkt->org, &p_org);
	if (peer->flip > 0)
		myorg = &peer->borg;
	else
		myorg = &peer->aorg;

	if (L_ISZERO(&p_org) ||
	    L_ISZERO( myorg) ||
	    !L_ISEQU(&p_org, myorg)) {
		return INVALIDNAK;
	}

	/* If we ever passed all that checks, we should be safe. Well,
	 * as safe as we can ever be with an unauthenticated crypto-nak.
	 */
	return VALIDNAK;
}