#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int32 ;
struct pkt {int /*<<< orphan*/ * exten; int /*<<< orphan*/  xmt; int /*<<< orphan*/  rec; int /*<<< orphan*/  org; int /*<<< orphan*/  reftime; int /*<<< orphan*/  refid; void* rootdisp; void* rootdelay; int /*<<< orphan*/  precision; void* ppoll; int /*<<< orphan*/  stratum; void* li_vn_mode; } ;
struct recvbuf {size_t recv_length; int /*<<< orphan*/  recv_srcadr; TYPE_1__* dstadr; int /*<<< orphan*/  recv_time; struct pkt recv_pkt; } ;
struct exten {int dummy; } ;
typedef  int /*<<< orphan*/  l_fp ;
typedef  scalar_t__ keyid_t ;
struct TYPE_5__ {scalar_t__ in_progress; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  sin; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_RESP ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  DTOFP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTOUFP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTONL_FP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* HTONS_FP (int /*<<< orphan*/ ) ; 
 int INT_MCASTOPEN ; 
 int /*<<< orphan*/  LEAP_NOTINSYNC ; 
 size_t LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  L_SUB (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t MAX_MAC_LEN ; 
 scalar_t__ NTP_MAXKEY ; 
 void* PKT_LI_VN_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PKT_VERSION (void*) ; 
 int RES_KOD ; 
 int RES_MSSNTP ; 
 int /*<<< orphan*/  STRATUM_PKT_UNSPEC ; 
 int /*<<< orphan*/  STRATUM_TO_PKT (int /*<<< orphan*/ ) ; 
 scalar_t__ authencrypt (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  authtrust (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convertLFPToRefID (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_xmit (int /*<<< orphan*/ *,struct pkt*,struct recvbuf*,size_t,struct exten*,scalar_t__) ; 
 int /*<<< orphan*/  current_time ; 
 TYPE_1__* findinterface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_systime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 TYPE_2__ leap_smear ; 
 int /*<<< orphan*/  leap_smear_add_offs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lfptoa (int /*<<< orphan*/ *,int) ; 
 void* max (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ntoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntp_minpoll ; 
 int /*<<< orphan*/  send_via_ntp_signd (struct recvbuf*,int,scalar_t__,int,struct pkt*) ; 
 int /*<<< orphan*/  sendpkt (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,struct pkt*,size_t) ; 
 scalar_t__ session_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_authdelay ; 
 int /*<<< orphan*/  sys_kodsent ; 
 int /*<<< orphan*/  sys_precision ; 
 scalar_t__ sys_private ; 
 int /*<<< orphan*/  sys_refid ; 
 int /*<<< orphan*/  sys_reftime ; 
 int /*<<< orphan*/  sys_rootdelay ; 
 int /*<<< orphan*/  sys_rootdisp ; 
 int /*<<< orphan*/  sys_stratum ; 
 int /*<<< orphan*/  xmt_leap ; 

__attribute__((used)) static void
fast_xmit(
	struct recvbuf *rbufp,	/* receive packet pointer */
	int	xmode,		/* receive mode */
	keyid_t	xkeyid,		/* transmit key ID */
	int	flags		/* restrict mask */
	)
{
	struct pkt xpkt;	/* transmit packet structure */
	struct pkt *rpkt;	/* receive packet structure */
	l_fp	xmt_tx, xmt_ty;
	size_t	sendlen;
#ifdef AUTOKEY
	u_int32	temp32;
#endif

	/*
	 * Initialize transmit packet header fields from the receive
	 * buffer provided. We leave the fields intact as received, but
	 * set the peer poll at the maximum of the receive peer poll and
	 * the system minimum poll (ntp_minpoll). This is for KoD rate
	 * control and not strictly specification compliant, but doesn't
	 * break anything.
	 *
	 * If the gazinta was from a multicast address, the gazoutta
	 * must go out another way.
	 */
	rpkt = &rbufp->recv_pkt;
	if (rbufp->dstadr->flags & INT_MCASTOPEN)
		rbufp->dstadr = findinterface(&rbufp->recv_srcadr);

	/*
	 * If this is a kiss-o'-death (KoD) packet, show leap
	 * unsynchronized, stratum zero, reference ID the four-character
	 * kiss code and system root delay. Note we don't reveal the
	 * local time, so these packets can't be used for
	 * synchronization.
	 */
	if (flags & RES_KOD) {
		sys_kodsent++;
		xpkt.li_vn_mode = PKT_LI_VN_MODE(LEAP_NOTINSYNC,
		    PKT_VERSION(rpkt->li_vn_mode), xmode);
		xpkt.stratum = STRATUM_PKT_UNSPEC;
		xpkt.ppoll = max(rpkt->ppoll, ntp_minpoll);
		xpkt.precision = rpkt->precision;
		memcpy(&xpkt.refid, "RATE", 4);
		xpkt.rootdelay = rpkt->rootdelay;
		xpkt.rootdisp = rpkt->rootdisp;
		xpkt.reftime = rpkt->reftime;
		xpkt.org = rpkt->xmt;
		xpkt.rec = rpkt->xmt;
		xpkt.xmt = rpkt->xmt;

	/*
	 * This is a normal packet. Use the system variables.
	 */
	} else {
#ifdef LEAP_SMEAR
		/*
		 * Make copies of the variables which can be affected by smearing.
		 */
		l_fp this_ref_time;
		l_fp this_recv_time;
#endif

		/*
		 * If we are inside the leap smear interval we add the current smear offset to
		 * the packet receive time, to the packet transmit time, and eventually to the
		 * reftime to make sure the reftime isn't later than the transmit/receive times.
		 */
		xpkt.li_vn_mode = PKT_LI_VN_MODE(xmt_leap,
		    PKT_VERSION(rpkt->li_vn_mode), xmode);

		xpkt.stratum = STRATUM_TO_PKT(sys_stratum);
		xpkt.ppoll = max(rpkt->ppoll, ntp_minpoll);
		xpkt.precision = sys_precision;
		xpkt.refid = sys_refid;
		xpkt.rootdelay = HTONS_FP(DTOFP(sys_rootdelay));
		xpkt.rootdisp = HTONS_FP(DTOUFP(sys_rootdisp));

#ifdef LEAP_SMEAR
		this_ref_time = sys_reftime;
		if (leap_smear.in_progress) {
			leap_smear_add_offs(&this_ref_time, NULL);
			xpkt.refid = convertLFPToRefID(leap_smear.offset);
			DPRINTF(2, ("fast_xmit: leap_smear.in_progress: refid %8x, smear %s\n",
				ntohl(xpkt.refid),
				lfptoa(&leap_smear.offset, 8)
				));
		}
		HTONL_FP(&this_ref_time, &xpkt.reftime);
#else
		HTONL_FP(&sys_reftime, &xpkt.reftime);
#endif

		xpkt.org = rpkt->xmt;

#ifdef LEAP_SMEAR
		this_recv_time = rbufp->recv_time;
		if (leap_smear.in_progress)
			leap_smear_add_offs(&this_recv_time, NULL);
		HTONL_FP(&this_recv_time, &xpkt.rec);
#else
		HTONL_FP(&rbufp->recv_time, &xpkt.rec);
#endif

		get_systime(&xmt_tx);
#ifdef LEAP_SMEAR
		if (leap_smear.in_progress)
			leap_smear_add_offs(&xmt_tx, &this_recv_time);
#endif
		HTONL_FP(&xmt_tx, &xpkt.xmt);
	}

#ifdef HAVE_NTP_SIGND
	if (flags & RES_MSSNTP) {
		send_via_ntp_signd(rbufp, xmode, xkeyid, flags, &xpkt);
		return;
	}
#endif /* HAVE_NTP_SIGND */

	/*
	 * If the received packet contains a MAC, the transmitted packet
	 * is authenticated and contains a MAC. If not, the transmitted
	 * packet is not authenticated.
	 */
	sendlen = LEN_PKT_NOMAC;
	if (rbufp->recv_length == sendlen) {
		sendpkt(&rbufp->recv_srcadr, rbufp->dstadr, 0, &xpkt,
		    sendlen);
		DPRINTF(1, ("fast_xmit: at %ld %s->%s mode %d len %lu\n",
			    current_time, stoa(&rbufp->dstadr->sin),
			    stoa(&rbufp->recv_srcadr), xmode,
			    (u_long)sendlen));
		return;
	}

	/*
	 * The received packet contains a MAC, so the transmitted packet
	 * must be authenticated. For symmetric key cryptography, use
	 * the predefined and trusted symmetric keys to generate the
	 * cryptosum. For autokey cryptography, use the server private
	 * value to generate the cookie, which is unique for every
	 * source-destination-key ID combination.
	 */
#ifdef AUTOKEY
	if (xkeyid > NTP_MAXKEY) {
		keyid_t cookie;

		/*
		 * The only way to get here is a reply to a legitimate
		 * client request message, so the mode must be
		 * MODE_SERVER. If an extension field is present, there
		 * can be only one and that must be a command. Do what
		 * needs, but with private value of zero so the poor
		 * jerk can decode it. If no extension field is present,
		 * use the cookie to generate the session key.
		 */
		cookie = session_key(&rbufp->recv_srcadr,
		    &rbufp->dstadr->sin, 0, sys_private, 0);
		if ((size_t)rbufp->recv_length > sendlen + MAX_MAC_LEN) {
			session_key(&rbufp->dstadr->sin,
			    &rbufp->recv_srcadr, xkeyid, 0, 2);
			temp32 = CRYPTO_RESP;
			rpkt->exten[0] |= htonl(temp32);
			sendlen += crypto_xmit(NULL, &xpkt, rbufp,
			    sendlen, (struct exten *)rpkt->exten,
			    cookie);
		} else {
			session_key(&rbufp->dstadr->sin,
			    &rbufp->recv_srcadr, xkeyid, cookie, 2);
		}
	}
#endif	/* AUTOKEY */
	get_systime(&xmt_tx);
	sendlen += authencrypt(xkeyid, (u_int32 *)&xpkt, sendlen);
#ifdef AUTOKEY
	if (xkeyid > NTP_MAXKEY)
		authtrust(xkeyid, 0);
#endif	/* AUTOKEY */
	sendpkt(&rbufp->recv_srcadr, rbufp->dstadr, 0, &xpkt, sendlen);
	get_systime(&xmt_ty);
	L_SUB(&xmt_ty, &xmt_tx);
	sys_authdelay = xmt_ty;
	DPRINTF(1, ("fast_xmit: at %ld %s->%s mode %d keyid %08x len %lu\n",
		    current_time, ntoa(&rbufp->dstadr->sin),
		    ntoa(&rbufp->recv_srcadr), xmode, xkeyid,
		    (u_long)sendlen));
}