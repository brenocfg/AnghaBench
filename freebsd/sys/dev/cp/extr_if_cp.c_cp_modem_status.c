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
struct TYPE_9__ {scalar_t__ running; TYPE_1__* board; } ;
typedef  TYPE_2__ drv_t ;
struct TYPE_10__ {scalar_t__ rts; scalar_t__ dtr; TYPE_2__* sys; } ;
typedef  TYPE_3__ cp_chan_t ;
typedef  int /*<<< orphan*/  bdrv_t ;
struct TYPE_8__ {int /*<<< orphan*/ * sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_UNLOCK (int /*<<< orphan*/ *) ; 
 int TIOCM_CD ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_LE ; 
 int TIOCM_RTS ; 
 scalar_t__ cp_get_cd (TYPE_3__*) ; 
 scalar_t__ cp_get_cts (TYPE_3__*) ; 
 scalar_t__ cp_get_dsr (TYPE_3__*) ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int cp_modem_status (cp_chan_t *c)
{
	drv_t *d = c->sys;
	bdrv_t *bd = d->board->sys;
	int status, s;

	status = d->running ? TIOCM_LE : 0;
	s = splimp ();
	CP_LOCK (bd);
	if (cp_get_cd  (c)) status |= TIOCM_CD;
	if (cp_get_cts (c)) status |= TIOCM_CTS;
	if (cp_get_dsr (c)) status |= TIOCM_DSR;
	if (c->dtr)	    status |= TIOCM_DTR;
	if (c->rts)	    status |= TIOCM_RTS;
	CP_UNLOCK (bd);
	splx (s);
	return status;
}