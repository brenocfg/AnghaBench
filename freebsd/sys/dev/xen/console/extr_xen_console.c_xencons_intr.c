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
struct xencons_priv {int /*<<< orphan*/  altbrk; int /*<<< orphan*/  opened; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 scalar_t__ kdb_active ; 
 int /*<<< orphan*/  kdb_alt_break (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 struct xencons_priv* tty_softc (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 int xencons_getc (struct xencons_priv*) ; 
 int /*<<< orphan*/  xencons_rx (struct xencons_priv*) ; 
 int /*<<< orphan*/  xencons_tx_flush (struct xencons_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xencons_intr(void *arg)
{
	struct tty *tp;
	struct xencons_priv *cons;
	int ret;

	tp = arg;
	cons = tty_softc(tp);

	/*
	 * The input will be used by the low-level console when KDB is active
	 */
	if (kdb_active)
		return;

	/*
	 * It's not necessary to retrieve input when the tty is not opened
	 */
	if (!cons->opened)
		return;

	xencons_rx(cons);

	tty_lock(tp);
	while ((ret = xencons_getc(cons)) != -1) {
#ifdef KDB
		kdb_alt_break(ret, &cons->altbrk);
#endif
		ttydisc_rint(tp, ret, 0);
	}
	ttydisc_rint_done(tp);
	tty_unlock(tp);

	/* Try to flush remaining characters if necessary */
	xencons_tx_flush(cons, 0);
}