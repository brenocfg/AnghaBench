#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty {int dummy; } ;
struct dcons_softc {struct tty* tty; } ;

/* Variables and functions */
 int DCONS_NPORT ; 
 int DCONS_POLL_IDLE ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct tty*) ; 
 int /*<<< orphan*/  dcons_callout ; 
 int dcons_os_checkc_nopoll (struct dcons_softc*) ; 
 int hz ; 
 int poll_hz ; 
 int poll_idle ; 
 struct dcons_softc* sc ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 

__attribute__((used)) static void
dcons_timeout(void *v)
{
	struct	tty *tp;
	struct dcons_softc *dc;
	int i, c, polltime;

	for (i = 0; i < DCONS_NPORT; i ++) {
		dc = &sc[i];
		tp = dc->tty;

		tty_lock(tp);
		while ((c = dcons_os_checkc_nopoll(dc)) != -1) {
			ttydisc_rint(tp, c, 0);
			poll_idle = 0;
		}
		ttydisc_rint_done(tp);
		tty_unlock(tp);
	}
	poll_idle++;
	polltime = hz;
	if (poll_idle <= (poll_hz * DCONS_POLL_IDLE))
		polltime /= poll_hz;
	callout_reset(&dcons_callout, polltime, dcons_timeout, tp);
}