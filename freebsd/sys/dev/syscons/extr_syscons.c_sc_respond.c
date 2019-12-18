#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct tty {int dummy; } ;
struct TYPE_6__ {TYPE_4__* sc; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_7__ {TYPE_1__* cur_scp; } ;
struct TYPE_5__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 struct tty* SC_DEV (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_opened_ns (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint_simple (struct tty*,int /*<<< orphan*/  const*,int) ; 

void
sc_respond(scr_stat *scp, const u_char *p, int count, int wakeup) 
{
    struct tty *tp;

    tp = SC_DEV(scp->sc, scp->sc->cur_scp->index);
    if (!tty_opened_ns(tp))
	return;
    ttydisc_rint_simple(tp, p, count);
    if (wakeup) {
	/* XXX: we can't always call ttydisc_rint_done() here! */
	ttydisc_rint_done(tp);
    }
}