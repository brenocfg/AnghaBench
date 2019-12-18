#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tty {TYPE_2__* t_sc; } ;
struct TYPE_9__ {TYPE_3__* chan; TYPE_1__* board; } ;
typedef  TYPE_2__ drv_t ;
typedef  int /*<<< orphan*/  bdrv_t ;
struct TYPE_10__ {scalar_t__ rts; scalar_t__ dtr; } ;
struct TYPE_8__ {int /*<<< orphan*/ * sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CX_UNLOCK (int /*<<< orphan*/ *) ; 
 int SER_CTS ; 
 int SER_DCD ; 
 int SER_DSR ; 
 int SER_DTR ; 
 int SER_RTS ; 
 scalar_t__ cx_get_cd (TYPE_3__*) ; 
 scalar_t__ cx_get_cts (TYPE_3__*) ; 
 scalar_t__ cx_get_dsr (TYPE_3__*) ; 
 int /*<<< orphan*/  cx_set_dtr (TYPE_3__*,int) ; 
 int /*<<< orphan*/  cx_set_rts (TYPE_3__*,int) ; 

__attribute__((used)) static int cx_tmodem (struct tty *tp, int sigon, int sigoff)
{
	drv_t *d;
	bdrv_t *bd;

	d = tp->t_sc;
	bd = d->board->sys;

	CX_LOCK (bd);
	if (!sigon && !sigoff) {
		if (cx_get_dsr (d->chan)) sigon |= SER_DSR;
		if (cx_get_cd  (d->chan)) sigon |= SER_DCD;
		if (cx_get_cts (d->chan)) sigon |= SER_CTS;
		if (d->chan->dtr)	  sigon |= SER_DTR;
		if (d->chan->rts)	  sigon |= SER_RTS;
		CX_UNLOCK (bd);
		return sigon;
	}

	if (sigon & SER_DTR)
		cx_set_dtr (d->chan, 1);
	if (sigoff & SER_DTR)
		cx_set_dtr (d->chan, 0);
	if (sigon & SER_RTS)
		cx_set_rts (d->chan, 1);
	if (sigoff & SER_RTS)
		cx_set_rts (d->chan, 0);
	CX_UNLOCK (bd);

	return (0);
}