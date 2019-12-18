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
struct nmdmpart {struct tty* np_tty; struct nmdmpart* np_other; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 scalar_t__ tty_opened (struct tty*) ; 
 int /*<<< orphan*/  tty_rel_gone (struct tty*) ; 
 struct nmdmpart* tty_softc (struct tty*) ; 

__attribute__((used)) static void
nmdm_close(struct tty *tp)
{
	struct nmdmpart *np;
	struct nmdmpart *onp;
	struct tty *otp;

	np = tty_softc(tp);
	onp = np->np_other;
	otp = onp->np_tty;

	/* If second part is opened, do not destroy ourselves. */
	if (tty_opened(otp))
		return;

	/* Shut down self. */
	tty_rel_gone(tp);

	/* Shut down second part. */
	tty_lock(tp);
	onp = np->np_other;
	if (onp == NULL)
		return;
	otp = onp->np_tty;
	tty_rel_gone(otp);
	tty_lock(tp);
}