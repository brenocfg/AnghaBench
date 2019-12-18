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
typedef  void* u_int ;
typedef  scalar_t__ u_char ;
struct pkt {int /*<<< orphan*/  refid; int /*<<< orphan*/  precision; int /*<<< orphan*/  exten; int /*<<< orphan*/  ppoll; int /*<<< orphan*/  stratum; int /*<<< orphan*/  li_vn_mode; int /*<<< orphan*/  xmt; int /*<<< orphan*/  rec; int /*<<< orphan*/  org; int /*<<< orphan*/  reftime; int /*<<< orphan*/  rootdisp; int /*<<< orphan*/  rootdelay; } ;
struct peer {int flash; int hpoll; void* dst; double rootdelay; double rootdisp; scalar_t__ retry; int reach; scalar_t__ burst; int minpoll; scalar_t__ flip; void* borg; void* aorg; int flags; double xleave; int delay; double offset; unsigned int ppoll; scalar_t__ t21_last; scalar_t__ t34_bytes; int t21_bytes; double t21; double r21; double t34; double r34; scalar_t__ hmode; int crypto; scalar_t__ bias; scalar_t__ pmode; int /*<<< orphan*/  precision; void* nextdate; void* timereachable; void* reftime; int /*<<< orphan*/  refid; void* stratum; scalar_t__ leap; TYPE_1__* dstadr; int /*<<< orphan*/  srcadr; int /*<<< orphan*/  processed; int /*<<< orphan*/  seldisptoolarge; } ;
typedef  int /*<<< orphan*/  statstr ;
typedef  void* l_fp ;
struct TYPE_2__ {int /*<<< orphan*/  sin; } ;

/* Variables and functions */
 int CRYPTO_FLAG_ALL ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int FLAG_BC_VOL ; 
 int FLAG_SKEY ; 
 int FLAG_XB ; 
 double FPTOD (int /*<<< orphan*/ ) ; 
 scalar_t__ LEAP_NOTINSYNC ; 
 int /*<<< orphan*/  LFPTOD (void**,double) ; 
 double LOGTOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L_SUB (void**,void**) ; 
 double MAXDISPERSE ; 
 void* MIN_V4_PKT_LEN ; 
 void* MODE_BCLIENT ; 
 scalar_t__ MODE_BROADCAST ; 
 scalar_t__ MODE_CLIENT ; 
 int /*<<< orphan*/  NTOHL_FP (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  NTOHS_FP (int /*<<< orphan*/ ) ; 
 scalar_t__ NTP_IBURST ; 
 int NTP_MAXSTRLEN ; 
 int /*<<< orphan*/  NTP_SHIFT ; 
 int /*<<< orphan*/  PEVNT_REACH ; 
 int /*<<< orphan*/  PEVNT_XERR ; 
 scalar_t__ PKT_LEAP (int /*<<< orphan*/ ) ; 
 scalar_t__ PKT_MODE (int /*<<< orphan*/ ) ; 
 int PKT_TEST_MASK ; 
 scalar_t__ PKT_TO_STRATUM (int /*<<< orphan*/ ) ; 
 scalar_t__ PKT_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRATUM_UNSPEC ; 
 int TEST11 ; 
 int TEST6 ; 
 int TEST7 ; 
 int /*<<< orphan*/  clock_filter (struct peer*,scalar_t__,double,double) ; 
 double clock_phi ; 
 void* current_time ; 
 int fabs (double) ; 
 double max (double,double) ; 
 void* min (int,int /*<<< orphan*/ ) ; 
 int peer_unfit (struct peer*) ; 
 int /*<<< orphan*/  poll_update (struct peer*,int) ; 
 int /*<<< orphan*/  record_raw_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,void**,void**,void**,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,int /*<<< orphan*/ ,void*,scalar_t__*) ; 
 int /*<<< orphan*/  report_event (int /*<<< orphan*/ ,struct peer*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,double,double) ; 
 double sys_bdelay ; 
 scalar_t__ sys_ceiling ; 
 scalar_t__ sys_floor ; 
 int /*<<< orphan*/  sys_precision ; 
 int /*<<< orphan*/  sys_processed ; 
 int /*<<< orphan*/  unpeer (struct peer*) ; 

void
process_packet(
	register struct peer *peer,
	register struct pkt *pkt,
	u_int	len
	)
{
	double	t34, t21;
	double	p_offset, p_del, p_disp;
	l_fp	p_rec, p_xmt, p_org, p_reftime, ci;
	u_char	pmode, pleap, pversion, pstratum;
	char	statstr[NTP_MAXSTRLEN];
#ifdef ASSYM
	int	itemp;
	double	etemp, ftemp, td;
#endif /* ASSYM */

#if 0
	sys_processed++;
	peer->processed++;
#endif
	p_del = FPTOD(NTOHS_FP(pkt->rootdelay));
	p_offset = 0;
	p_disp = FPTOD(NTOHS_FP(pkt->rootdisp));
	NTOHL_FP(&pkt->reftime, &p_reftime);
	NTOHL_FP(&pkt->org, &p_org);
	NTOHL_FP(&pkt->rec, &p_rec);
	NTOHL_FP(&pkt->xmt, &p_xmt);
	pmode = PKT_MODE(pkt->li_vn_mode);
	pleap = PKT_LEAP(pkt->li_vn_mode);
	pversion = PKT_VERSION(pkt->li_vn_mode);
	pstratum = PKT_TO_STRATUM(pkt->stratum);

	/**/

	/**/

	/*
	 * Verify the server is synchronized; that is, the leap bits,
	 * stratum and root distance are valid.
	 */
	if (   pleap == LEAP_NOTINSYNC		/* test 6 */
	    || pstratum < sys_floor || pstratum >= sys_ceiling)
		peer->flash |= TEST6;		/* bad synch or strat */
	if (p_del / 2 + p_disp >= MAXDISPERSE)	/* test 7 */
		peer->flash |= TEST7;		/* bad header */

	/*
	 * If any tests fail at this point, the packet is discarded.
	 * Note that some flashers may have already been set in the
	 * receive() routine.
	 */
	if (peer->flash & PKT_TEST_MASK) {
		peer->seldisptoolarge++;
		DPRINTF(1, ("packet: flash header %04x\n",
			    peer->flash));
		poll_update(peer, peer->hpoll);	/* ppoll updated? */
		return;
	}

	/**/

#if 1
	sys_processed++;
	peer->processed++;
#endif

	/*
	 * Capture the header values in the client/peer association..
	 */
	record_raw_stats(&peer->srcadr,
	    peer->dstadr ? &peer->dstadr->sin : NULL,
	    &p_org, &p_rec, &p_xmt, &peer->dst,
	    pleap, pversion, pmode, pstratum, pkt->ppoll, pkt->precision,
	    p_del, p_disp, pkt->refid,
	    len - MIN_V4_PKT_LEN, (u_char *)&pkt->exten);
	peer->leap = pleap;
	peer->stratum = min(pstratum, STRATUM_UNSPEC);
	peer->pmode = pmode;
	peer->precision = pkt->precision;
	peer->rootdelay = p_del;
	peer->rootdisp = p_disp;
	peer->refid = pkt->refid;		/* network byte order */
	peer->reftime = p_reftime;

	/*
	 * First, if either burst mode is armed, enable the burst.
	 * Compute the headway for the next packet and delay if
	 * necessary to avoid exceeding the threshold.
	 */
	if (peer->retry > 0) {
		peer->retry = 0;
		if (peer->reach)
			peer->burst = min(1 << (peer->hpoll -
			    peer->minpoll), NTP_SHIFT) - 1;
		else
			peer->burst = NTP_IBURST - 1;
		if (peer->burst > 0)
			peer->nextdate = current_time;
	}
	poll_update(peer, peer->hpoll);

	/**/

	/*
	 * If the peer was previously unreachable, raise a trap. In any
	 * case, mark it reachable.
	 */
	if (!peer->reach) {
		report_event(PEVNT_REACH, peer, NULL);
		peer->timereachable = current_time;
	}
	peer->reach |= 1;

	/*
	 * For a client/server association, calculate the clock offset,
	 * roundtrip delay and dispersion. The equations are reordered
	 * from the spec for more efficient use of temporaries. For a
	 * broadcast association, offset the last measurement by the
	 * computed delay during the client/server volley. Note the
	 * computation of dispersion includes the system precision plus
	 * that due to the frequency error since the origin time.
	 *
	 * It is very important to respect the hazards of overflow. The
	 * only permitted operation on raw timestamps is subtraction,
	 * where the result is a signed quantity spanning from 68 years
	 * in the past to 68 years in the future. To avoid loss of
	 * precision, these calculations are done using 64-bit integer
	 * arithmetic. However, the offset and delay calculations are
	 * sums and differences of these first-order differences, which
	 * if done using 64-bit integer arithmetic, would be valid over
	 * only half that span. Since the typical first-order
	 * differences are usually very small, they are converted to 64-
	 * bit doubles and all remaining calculations done in floating-
	 * double arithmetic. This preserves the accuracy while
	 * retaining the 68-year span.
	 *
	 * There are three interleaving schemes, basic, interleaved
	 * symmetric and interleaved broadcast. The timestamps are
	 * idioscyncratically different. See the onwire briefing/white
	 * paper at www.eecis.udel.edu/~mills for details.
	 *
	 * Interleaved symmetric mode
	 * t1 = peer->aorg/borg, t2 = peer->rec, t3 = p_xmt,
	 * t4 = peer->dst
	 */
	if (peer->flip != 0) {
		ci = p_xmt;				/* t3 - t4 */
		L_SUB(&ci, &peer->dst);
		LFPTOD(&ci, t34);
		ci = p_rec;				/* t2 - t1 */
		if (peer->flip > 0)
			L_SUB(&ci, &peer->borg);
		else
			L_SUB(&ci, &peer->aorg);
		LFPTOD(&ci, t21);
		p_del = t21 - t34;
		p_offset = (t21 + t34) / 2.;
		if (p_del < 0 || p_del > 1.) {
			snprintf(statstr, sizeof(statstr),
			    "t21 %.6f t34 %.6f", t21, t34);
			report_event(PEVNT_XERR, peer, statstr);
			return;
		}

	/*
	 * Broadcast modes
	 */
	} else if (peer->pmode == MODE_BROADCAST) {

		/*
		 * Interleaved broadcast mode. Use interleaved timestamps.
		 * t1 = peer->borg, t2 = p_org, t3 = p_org, t4 = aorg
		 */
		if (peer->flags & FLAG_XB) {
			ci = p_org;			/* delay */
			L_SUB(&ci, &peer->aorg);
			LFPTOD(&ci, t34);
			ci = p_org;			/* t2 - t1 */
			L_SUB(&ci, &peer->borg);
			LFPTOD(&ci, t21);
			peer->aorg = p_xmt;
			peer->borg = peer->dst;
			if (t34 < 0 || t34 > 1.) {
				/* drop all if in the initial volley */
				if (FLAG_BC_VOL & peer->flags)
					goto bcc_init_volley_fail;
				snprintf(statstr, sizeof(statstr),
				    "offset %.6f delay %.6f", t21, t34);
				report_event(PEVNT_XERR, peer, statstr);
				return;
			}
			p_offset = t21;
			peer->xleave = t34;

		/*
		 * Basic broadcast - use direct timestamps.
		 * t3 = p_xmt, t4 = peer->dst
		 */
		} else {
			ci = p_xmt;		/* t3 - t4 */
			L_SUB(&ci, &peer->dst);
			LFPTOD(&ci, t34);
			p_offset = t34;
		}

		/*
		 * When calibration is complete and the clock is
		 * synchronized, the bias is calculated as the difference
		 * between the unicast timestamp and the broadcast
		 * timestamp. This works for both basic and interleaved
		 * modes.
		 * [Bug 3031] Don't keep this peer when the delay
		 * calculation gives reason to suspect clock steps.
		 * This is assumed for delays > 50ms.
		 */
		if (FLAG_BC_VOL & peer->flags) {
			peer->flags &= ~FLAG_BC_VOL;
			peer->delay = fabs(peer->offset - p_offset) * 2;
			DPRINTF(2, ("broadcast volley: initial delay=%.6f\n",
				peer->delay));
			if (peer->delay > fabs(sys_bdelay)) {
		bcc_init_volley_fail:
				DPRINTF(2, ("%s", "broadcast volley: initial delay exceeds limit\n"));
				unpeer(peer);
				return;
			}
		}
		peer->nextdate = current_time + (1u << peer->ppoll) - 2u;
		p_del = peer->delay;
		p_offset += p_del / 2;


	/*
	 * Basic mode, otherwise known as the old fashioned way.
	 *
	 * t1 = p_org, t2 = p_rec, t3 = p_xmt, t4 = peer->dst
	 */
	} else {
		ci = p_xmt;				/* t3 - t4 */
		L_SUB(&ci, &peer->dst);
		LFPTOD(&ci, t34);
		ci = p_rec;				/* t2 - t1 */
		L_SUB(&ci, &p_org);
		LFPTOD(&ci, t21);
		p_del = fabs(t21 - t34);
		p_offset = (t21 + t34) / 2.;
	}
	p_del = max(p_del, LOGTOD(sys_precision));
	p_disp = LOGTOD(sys_precision) + LOGTOD(peer->precision) +
	    clock_phi * p_del;

#if ASSYM
	/*
	 * This code calculates the outbound and inbound data rates by
	 * measuring the differences between timestamps at different
	 * packet lengths. This is helpful in cases of large asymmetric
	 * delays commonly experienced on deep space communication
	 * links.
	 */
	if (peer->t21_last > 0 && peer->t34_bytes > 0) {
		itemp = peer->t21_bytes - peer->t21_last;
		if (itemp > 25) {
			etemp = t21 - peer->t21;
			if (fabs(etemp) > 1e-6) {
				ftemp = itemp / etemp;
				if (ftemp > 1000.)
					peer->r21 = ftemp;
			}
		}
		itemp = len - peer->t34_bytes;
		if (itemp > 25) {
			etemp = -t34 - peer->t34;
			if (fabs(etemp) > 1e-6) {
				ftemp = itemp / etemp;
				if (ftemp > 1000.)
					peer->r34 = ftemp;
			}
		}
	}

	/*
	 * The following section compensates for different data rates on
	 * the outbound (d21) and inbound (t34) directions. To do this,
	 * it finds t such that r21 * t - r34 * (d - t) = 0, where d is
	 * the roundtrip delay. Then it calculates the correction as a
	 * fraction of d.
	 */
	peer->t21 = t21;
	peer->t21_last = peer->t21_bytes;
	peer->t34 = -t34;
	peer->t34_bytes = len;
	DPRINTF(2, ("packet: t21 %.9lf %d t34 %.9lf %d\n", peer->t21,
		    peer->t21_bytes, peer->t34, peer->t34_bytes));
	if (peer->r21 > 0 && peer->r34 > 0 && p_del > 0) {
		if (peer->pmode != MODE_BROADCAST)
			td = (peer->r34 / (peer->r21 + peer->r34) -
			    .5) * p_del;
		else
			td = 0;

		/*
		 * Unfortunately, in many cases the errors are
		 * unacceptable, so for the present the rates are not
		 * used. In future, we might find conditions where the
		 * calculations are useful, so this should be considered
		 * a work in progress.
		 */
		t21 -= td;
		t34 -= td;
		DPRINTF(2, ("packet: del %.6lf r21 %.1lf r34 %.1lf %.6lf\n",
			    p_del, peer->r21 / 1e3, peer->r34 / 1e3,
			    td));
	}
#endif /* ASSYM */

	/*
	 * That was awesome. Now hand off to the clock filter.
	 */
	clock_filter(peer, p_offset + peer->bias, p_del, p_disp);

	/*
	 * If we are in broadcast calibrate mode, return to broadcast
	 * client mode when the client is fit and the autokey dance is
	 * complete.
	 */
	if (   (FLAG_BC_VOL & peer->flags)
	    && MODE_CLIENT == peer->hmode
	    && !(TEST11 & peer_unfit(peer))) {	/* distance exceeded */
#ifdef AUTOKEY
		if (peer->flags & FLAG_SKEY) {
			if (!(~peer->crypto & CRYPTO_FLAG_ALL))
				peer->hmode = MODE_BCLIENT;
		} else {
			peer->hmode = MODE_BCLIENT;
		}
#else	/* !AUTOKEY follows */
		peer->hmode = MODE_BCLIENT;
#endif	/* !AUTOKEY */
	}
}