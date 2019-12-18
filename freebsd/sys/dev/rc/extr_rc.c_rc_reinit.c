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
struct rc_softc {struct rc_chans* sc_channels; } ;
struct rc_chans {TYPE_1__* rc_tp; } ;
struct TYPE_2__ {int /*<<< orphan*/  t_termios; } ;

/* Variables and functions */
 int CD180_NCHAN ; 
 int /*<<< orphan*/  RC_FAKEID ; 
 int /*<<< orphan*/  rc_hwreset (struct rc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_param (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rc_reinit(struct rc_softc *sc)
{
	struct rc_chans *rc;
	int i;

	rc_hwreset(sc, RC_FAKEID);
	rc = sc->sc_channels;
	for (i = 0; i < CD180_NCHAN; i++, rc++)
		(void) rc_param(rc->rc_tp, &rc->rc_tp->t_termios);
}