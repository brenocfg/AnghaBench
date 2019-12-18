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
struct tty {int dummy; } ;
struct nmdmpart {TYPE_1__* np_other; scalar_t__ np_dcd; } ;
struct TYPE_2__ {int np_dcd; int /*<<< orphan*/  np_tty; } ;

/* Variables and functions */
 int SER_DCD ; 
 int SER_DTR ; 
 struct nmdmpart* tty_softc (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_modem (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nmdm_modem(struct tty *tp, int sigon, int sigoff)
{
	struct nmdmpart *np = tty_softc(tp);
	int i = 0;

	if (sigon || sigoff) {
		if (sigon & SER_DTR)
			np->np_other->np_dcd = 1;
		if (sigoff & SER_DTR)
			np->np_other->np_dcd = 0;

		ttydisc_modem(np->np_other->np_tty, np->np_other->np_dcd);

		return (0);
	} else {
		if (np->np_dcd)
			i |= SER_DCD;
		if (np->np_other->np_dcd)
			i |= SER_DTR;

		return (i);
	}
}