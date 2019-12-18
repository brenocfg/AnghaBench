#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tty {int t_ispeed; int t_ospeed; int t_cflag; TYPE_2__* t_sc; } ;
struct termios {int c_ospeed; int c_ispeed; int c_cflag; int c_iflag; int /*<<< orphan*/ * c_cc; } ;
struct TYPE_7__ {TYPE_3__* chan; TYPE_1__* board; } ;
typedef  TYPE_2__ drv_t ;
typedef  int /*<<< orphan*/  bdrv_t ;
struct TYPE_8__ {int /*<<< orphan*/  dtr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * sys; } ;

/* Variables and functions */
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int /*<<< orphan*/  CX_DEBUG2 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  CX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CX_UNLOCK (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int IXANY ; 
 int IXON ; 
 int PARENB ; 
 int PARODD ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  cx_set_async_param (TYPE_3__*,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_set_dtr (TYPE_3__*,int) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  ttyldoptim (struct tty*) ; 

__attribute__((used)) static int cx_param (struct tty *tp, struct termios *t)
{
	drv_t *d;
	bdrv_t *bd;
	int s, bits, parity;

	d = tp->t_sc;
	bd = d->board->sys;
	
	s = splhigh ();
	CX_LOCK (bd);
	if (t->c_ospeed == 0) {
		/* Clear DTR and RTS. */
		cx_set_dtr (d->chan, 0);
		CX_UNLOCK (bd);
		splx (s);
		CX_DEBUG2 (d, ("cx_param (hangup)\n"));
		return 0;
	}
	CX_DEBUG2 (d, ("cx_param\n"));

	/* Check requested parameters. */
	if (t->c_ospeed < 300 || t->c_ospeed > 256*1024) {
		CX_UNLOCK (bd);
		splx (s);
		return EINVAL;
	}
	if (t->c_ispeed && (t->c_ispeed < 300 || t->c_ispeed > 256*1024)) {
		CX_UNLOCK (bd);
		splx (s);
		return EINVAL;
	}

  	/* And copy them to tty and channel structures. */
	tp->t_ispeed = t->c_ispeed = tp->t_ospeed = t->c_ospeed;
	tp->t_cflag = t->c_cflag;

	/* Set character length and parity mode. */
	switch (t->c_cflag & CSIZE) {
	default:
	case CS8: bits = 8; break;
	case CS7: bits = 7; break;
	case CS6: bits = 6; break;
	case CS5: bits = 5; break;
	}

	parity = ((t->c_cflag & PARENB) ? 1 : 0) *
		 (1 + ((t->c_cflag & PARODD) ? 0 : 1));

	/* Set current channel number. */
	if (! d->chan->dtr)
		cx_set_dtr (d->chan, 1);

	ttyldoptim (tp);
	cx_set_async_param (d->chan, t->c_ospeed, bits, parity, (t->c_cflag & CSTOPB),
		!(t->c_cflag & PARENB), (t->c_cflag & CRTSCTS),
		(t->c_iflag & IXON), (t->c_iflag & IXANY),
		t->c_cc[VSTART], t->c_cc[VSTOP]);
	CX_UNLOCK (bd);
	splx (s);
	return 0;
}