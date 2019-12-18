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
struct TYPE_5__ {int cd; scalar_t__ tty; int /*<<< orphan*/ * chan; TYPE_1__* board; } ;
typedef  TYPE_2__ drv_t ;
typedef  int /*<<< orphan*/  cx_chan_t ;
typedef  int /*<<< orphan*/  bdrv_t ;
struct TYPE_4__ {int /*<<< orphan*/ * sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX_DEBUG (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  CX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CX_UNLOCK (int /*<<< orphan*/ *) ; 
 int cx_get_cd (int /*<<< orphan*/ *) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  ttyld_modem (scalar_t__,int) ; 

__attribute__((used)) static void cx_carrier (void *arg)
{
	drv_t *d = arg;
	bdrv_t *bd = d->board->sys;
	cx_chan_t *c = d->chan;
	int s, cd;

	s = splhigh ();
	CX_LOCK (bd);
	cd = cx_get_cd (c);
	if (d->cd != cd) {
		if (cd) {
			CX_DEBUG (d, ("carrier on\n"));
			d->cd = 1;
			CX_UNLOCK (bd);
			splx (s);
			if (d->tty)
				ttyld_modem(d->tty, 1);
		} else {
			CX_DEBUG (d, ("carrier loss\n"));
			d->cd = 0;
			CX_UNLOCK (bd);
			splx (s);
			if (d->tty)
				ttyld_modem(d->tty, 0);
		}
	} else {
		CX_UNLOCK (bd);
		splx (s);
	}
}