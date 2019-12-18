#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ dm; scalar_t__ css; scalar_t__ oofs; scalar_t__ ses; scalar_t__ bes; scalar_t__ es; scalar_t__ les; scalar_t__ uas; scalar_t__ rcrce; scalar_t__ crce; scalar_t__ fse; scalar_t__ bpv; } ;
struct TYPE_8__ {int /*<<< orphan*/  dm; int /*<<< orphan*/  css; int /*<<< orphan*/  oofs; int /*<<< orphan*/  ses; int /*<<< orphan*/  bes; int /*<<< orphan*/  es; int /*<<< orphan*/  les; int /*<<< orphan*/  uas; int /*<<< orphan*/  rcrce; int /*<<< orphan*/  crce; int /*<<< orphan*/  fse; int /*<<< orphan*/  bpv; } ;
struct TYPE_9__ {int cursec; scalar_t__ mode; int totsec; int degsec; int degerr; TYPE_4__ currnt; TYPE_2__ total; TYPE_4__* interval; int /*<<< orphan*/  status; TYPE_1__* board; scalar_t__ num; } ;
typedef  TYPE_3__ ct_chan_t ;
struct TYPE_7__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESTS_LOS ; 
 int /*<<< orphan*/  ESTS_NOALARM ; 
 int /*<<< orphan*/  ESTS_TSTERR ; 
 int /*<<< orphan*/  ESTS_TSTREQ ; 
 int /*<<< orphan*/  GERR (int /*<<< orphan*/ ) ; 
 int GERR_BPV0 ; 
 int GERR_BPV1 ; 
 int GERR_ERR0 ; 
 int GERR_ERR1 ; 
 int /*<<< orphan*/  GLDR (int /*<<< orphan*/ ) ; 
 int GLDR_LREQ0 ; 
 int GLDR_LREQ1 ; 
 scalar_t__ M_G703 ; 
 int ct_get_cd (TYPE_3__*) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

void ct_g703_timer (ct_chan_t *c)
{
	int bpv, cd, tsterr, tstreq;

	/* Count seconds.
	 * During the first second after the channel startup
	 * the status registers are not stable yet,
	 * we will so skip the first second. */
	++c->cursec;
	if (c->mode != M_G703)
		return;
	if (c->totsec + c->cursec <= 1)
		return;
	c->status = 0;

	cd = ct_get_cd (c);

	bpv = inb (GERR (c->board->port)) & (c->num ? GERR_BPV1 : GERR_BPV0);
	outb (GERR (c->board->port), bpv);

	tsterr = inb (GERR (c->board->port)) & (c->num ? GERR_ERR1 : GERR_ERR0);
	outb (GERR (c->board->port), tsterr);

	tstreq = inb (GLDR (c->board->port)) &
		(c->num ? GLDR_LREQ1 : GLDR_LREQ0);
	outb (GLDR (c->board->port), tstreq);

	/* Compute the SNMP-compatible channel status. */
	if (bpv)
		++c->currnt.bpv;	  /* bipolar violation */
	if (! cd)
		c->status |= ESTS_LOS;	  /* loss of signal */
	if (tsterr)
		c->status |= ESTS_TSTERR; /* test error */
	if (tstreq)
		c->status |= ESTS_TSTREQ; /* test code detected */

	if (! c->status)
		c->status = ESTS_NOALARM;

	/* Unavaiable second -- loss of carrier, or receiving test code. */
	if ((! cd) || tstreq)
		/* Unavailable second -- no other counters. */
		++c->currnt.uas;
	else {
		/* Line errored second -- any BPV. */
		if (bpv)
			++c->currnt.les;

		/* Collect data for computing
		 * degraded minutes. */
		++c->degsec;
		if (cd && bpv)
			++c->degerr;
	}

	/* Degraded minutes -- having more than 50% error intervals. */
	if (c->cursec / 60 == 0) {
		if (c->degerr*2 > c->degsec)
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
		memset (&c->currnt, 0, sizeof (c->currnt));

		c->totsec += c->cursec;
		c->cursec = 0;
	}
}