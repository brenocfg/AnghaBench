#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tty {int dummy; } ;
struct TYPE_10__ {int xsize; int ysize; TYPE_4__* sc; TYPE_1__* rndr; int /*<<< orphan*/  index; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_11__ {int blink_in_progress; int /*<<< orphan*/  cblink; scalar_t__ delayed_next_scr; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* draw ) (TYPE_2__*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  C_PREL (int /*<<< orphan*/ ) ; 
 scalar_t__ ISGRAPHSC (TYPE_2__*) ; 
 int SBT_1S ; 
 struct tty* SC_DEV (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void (*) (void*),TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_all (TYPE_2__*) ; 
 int /*<<< orphan*/  sc_switch_scr (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  sctty_outwakeup (struct tty*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ tty_opened_ns (struct tty*) ; 

__attribute__((used)) static void
blink_screen(void *arg)
{
    scr_stat *scp = arg;
    struct tty *tp;

    if (ISGRAPHSC(scp) || (scp->sc->blink_in_progress <= 1)) {
	scp->sc->blink_in_progress = 0;
    	mark_all(scp);
	tp = SC_DEV(scp->sc, scp->index);
	if (tty_opened_ns(tp))
	    sctty_outwakeup(tp);
	if (scp->sc->delayed_next_scr)
	    sc_switch_scr(scp->sc, scp->sc->delayed_next_scr - 1);
    }
    else {
	(*scp->rndr->draw)(scp, 0, scp->xsize*scp->ysize, 
			   scp->sc->blink_in_progress & 1);
	scp->sc->blink_in_progress--;
	callout_reset_sbt(&scp->sc->cblink, SBT_1S / 15, 0,
	    blink_screen, scp, C_PREL(0));
    }
}