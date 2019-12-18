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
struct xencons_priv {int dummy; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 struct xencons_priv* tty_softc (struct tty*) ; 
 int ttydisc_getc (struct tty*,char*,int) ; 
 int xencons_putc (struct xencons_priv*,char,int) ; 
 scalar_t__ xencons_tx_full (struct xencons_priv*) ; 

__attribute__((used)) static bool
xencons_tx(struct tty *tp)
{
	bool cons_full;
	char c;
	struct xencons_priv *cons;

	cons = tty_softc(tp);

	tty_lock_assert(tp, MA_OWNED);

	/*
	 * Don't transmit any character if the buffer is full. Otherwise,
	 * characters may be lost
	 */
	if (xencons_tx_full(cons))
		return (false);

	cons_full = false;
	while (!cons_full && ttydisc_getc(tp, &c, 1) == 1)
		cons_full = xencons_putc(cons, c, false);

	return (!cons_full);
}