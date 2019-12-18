#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ dm; scalar_t__ css; scalar_t__ oofs; scalar_t__ ses; scalar_t__ bes; scalar_t__ es; scalar_t__ les; scalar_t__ uas; scalar_t__ rcrce; scalar_t__ crce; scalar_t__ fse; scalar_t__ bpv; } ;
struct TYPE_7__ {int /*<<< orphan*/  dm; int /*<<< orphan*/  css; int /*<<< orphan*/  oofs; int /*<<< orphan*/  ses; int /*<<< orphan*/  bes; int /*<<< orphan*/  es; int /*<<< orphan*/  les; int /*<<< orphan*/  uas; int /*<<< orphan*/  rcrce; int /*<<< orphan*/  crce; int /*<<< orphan*/  fse; int /*<<< orphan*/  bpv; } ;
struct TYPE_9__ {scalar_t__ crc4; scalar_t__ cas; } ;
struct TYPE_11__ {scalar_t__ e1_first_int; int cursec; int degsec; unsigned long degerr; int totsec; TYPE_4__ currnt; TYPE_1__ total; TYPE_4__* interval; TYPE_3__ gopt; int /*<<< orphan*/  status; TYPE_2__* board; scalar_t__ num; } ;
typedef  TYPE_5__ ct_chan_t ;
struct TYPE_8__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 unsigned long CRCCR (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  DS_CRCCR1 ; 
 int /*<<< orphan*/  DS_CRCCR2 ; 
 int /*<<< orphan*/  DS_EBCR1 ; 
 int /*<<< orphan*/  DS_EBCR2 ; 
 int /*<<< orphan*/  DS_FASCR1 ; 
 int /*<<< orphan*/  DS_FASCR2 ; 
 int /*<<< orphan*/  DS_SR1 ; 
 int /*<<< orphan*/  DS_SR2 ; 
 int /*<<< orphan*/  DS_SSR ; 
 int /*<<< orphan*/  DS_VCR1 ; 
 int /*<<< orphan*/  DS_VCR2 ; 
 unsigned short E1CS0 (int /*<<< orphan*/ ) ; 
 unsigned short E1CS1 (int /*<<< orphan*/ ) ; 
 unsigned long EBCR (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  ESTS_AIS ; 
 int /*<<< orphan*/  ESTS_AIS16 ; 
 int /*<<< orphan*/  ESTS_FARLOF ; 
 int /*<<< orphan*/  ESTS_FARLOMF ; 
 int /*<<< orphan*/  ESTS_LOF ; 
 int /*<<< orphan*/  ESTS_LOMF ; 
 int /*<<< orphan*/  ESTS_LOS ; 
 int /*<<< orphan*/  ESTS_NOALARM ; 
 unsigned long FASCR (unsigned char,unsigned char) ; 
 unsigned char SR1_RCL ; 
 unsigned char SR1_RDMA ; 
 unsigned char SR1_RLOS ; 
 unsigned char SR1_RRA ; 
 unsigned char SR1_RSA1 ; 
 unsigned char SR1_RSLIP ; 
 unsigned char SR1_RUA1 ; 
 unsigned char SR2_SEC ; 
 unsigned char SSR_SYNC ; 
 unsigned char SSR_SYNC_CAS ; 
 unsigned char SSR_SYNC_CRC4 ; 
 unsigned long VCR (unsigned char,unsigned char) ; 
 unsigned char cte_in (unsigned short,int /*<<< orphan*/ ) ; 
 unsigned char cte_ins (unsigned short,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ct_e1timer_interrupt (ct_chan_t *c)
{
	unsigned short port;
	unsigned char sr1, sr2, ssr;
	unsigned long bpv, fas, crc4, ebit, pcv, oof;

	port = c->num ? E1CS1(c->board->port) : E1CS0(c->board->port);

	sr2 = cte_ins (port, DS_SR2, 0xff);
	/* is it timer interrupt ? */
	if (! (sr2 & SR2_SEC))
		return;

	/* first interrupts should be ignored */
	if (c->e1_first_int > 0) {
		c->e1_first_int --;
		return;
	}

	++c->cursec;
	c->status = 0;

	/* Compute the SNMP-compatible channel status. */
	sr1 = cte_ins (port, DS_SR1, 0xff);
	ssr = cte_in (port, DS_SSR);
	oof = 0;

	if (sr1 & (SR1_RCL | SR1_RLOS))
		c->status |= ESTS_LOS;		/* loss of signal */
	if (sr1 & SR1_RUA1)
		c->status |= ESTS_AIS;		/* receiving all ones */
	if (c->gopt.cas && (sr1 & SR1_RSA1))
		c->status |= ESTS_AIS16;	/* signaling all ones */
	if (c->gopt.cas && (sr1 & SR1_RDMA))
		c->status |= ESTS_FARLOMF;	/* alarm in timeslot 16 */
	if (sr1 & SR1_RRA)
		c->status |= ESTS_FARLOF;	/* far loss of framing */

	/* Controlled slip second -- any slip event. */
	if (sr1 & SR1_RSLIP) {
		++c->currnt.css;
	}

	if (ssr & SSR_SYNC) {
		c->status |= ESTS_LOF;		/* loss of framing */
		++oof;				/* out of framing */
	}
	if ((c->gopt.cas && (ssr & SSR_SYNC_CAS)) ||
	    (c->gopt.crc4 && (ssr & SSR_SYNC_CRC4))) {
		c->status |= ESTS_LOMF; 	/* loss of multiframing */
		++oof;				/* out of framing */
	}

	if (! c->status)
		c->status = ESTS_NOALARM;

	/* Get error counters. */
	bpv = VCR (cte_in (port, DS_VCR1), cte_in (port, DS_VCR2));
	fas = FASCR (cte_in (port, DS_FASCR1), cte_in (port, DS_FASCR2));
	crc4 = CRCCR (cte_in (port, DS_CRCCR1), cte_in (port, DS_CRCCR2));
	ebit = EBCR (cte_in (port, DS_EBCR1), cte_in (port, DS_EBCR2));

	c->currnt.bpv += bpv;
	c->currnt.fse += fas;
	if (c->gopt.crc4) {
		c->currnt.crce += crc4;
		c->currnt.rcrce += ebit;
	}

	/* Path code violation is frame sync error if CRC4 disabled,
	 * or CRC error if CRC4 enabled. */
	pcv = fas;
	if (c->gopt.crc4)
		pcv += crc4;

	/* Unavaiable second -- receiving all ones, or
	 * loss of carrier, or loss of signal. */
	if (sr1 & (SR1_RUA1 | SR1_RCL | SR1_RLOS))
		/* Unavailable second -- no other counters. */
		++c->currnt.uas;
	else {
		/* Line errored second -- any BPV. */
		if (bpv)
			++c->currnt.les;

		/* Errored second -- any PCV, or out of frame sync,
		 * or any slip events. */
		if (pcv || oof || (sr1 & SR1_RSLIP))
			++c->currnt.es;

		/* Severely errored framing second -- out of frame sync. */
		if (oof)
			++c->currnt.oofs;

		/* Severely errored seconds --
		 * 832 or more PCVs, or 2048 or more BPVs. */
		if (bpv >= 2048 || pcv >= 832)
			++c->currnt.ses;
		else {
			/* Bursty errored seconds --
			 * no SES and more than 1 PCV. */
			if (pcv > 1)
				++c->currnt.bes;

			/* Collect data for computing
			 * degraded minutes. */
			++c->degsec;
			c->degerr += bpv + pcv;
		}
	}

	/* Degraded minutes -- having error rate more than 10e-6,
	 * not counting unavailable and severely errored seconds. */
	if (c->cursec / 60 == 0) {
		if (c->degerr > c->degsec * 2048 / 1000)
			++c->currnt.dm;
		c->degsec = 0;
		c->degerr = 0;
	}

	/* Rotate statistics every 15 minutes. */
	if (c->cursec > 15*60) {
		int i;

		for (i=47; i>0; --i)
			c->interval[i] = c->interval[i-1];
		c->interval[0] = c->currnt;

		/* Accumulate total statistics. */
		c->total.bpv   += c->currnt.bpv;
		c->total.fse   += c->currnt.fse;
		c->total.crce  += c->currnt.crce;
		c->total.rcrce += c->currnt.rcrce;
		c->total.uas   += c->currnt.uas;
		c->total.les   += c->currnt.les;
		c->total.es    += c->currnt.es;
		c->total.bes   += c->currnt.bes;
		c->total.ses   += c->currnt.ses;
		c->total.oofs  += c->currnt.oofs;
		c->total.css   += c->currnt.css;
		c->total.dm    += c->currnt.dm;
		for (i=0; i<sizeof (c->currnt); ++i)
			*(((char *)(&c->currnt))+i)=0;

		c->totsec += c->cursec;
		c->cursec = 0;
	}
}