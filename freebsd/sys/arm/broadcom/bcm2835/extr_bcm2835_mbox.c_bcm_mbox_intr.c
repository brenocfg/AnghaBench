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
struct bcm_mbox_softc {int* have_message; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBOX_LOCK (struct bcm_mbox_softc*) ; 
 int /*<<< orphan*/  MBOX_UNLOCK (struct bcm_mbox_softc*) ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int STATUS_EMPTY ; 
 scalar_t__ bcm_mbox_read_msg (struct bcm_mbox_softc*,int*) ; 
 int mbox_read_4 (struct bcm_mbox_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static void
bcm_mbox_intr(void *arg)
{
	struct bcm_mbox_softc *sc = arg;
	int chan;

	MBOX_LOCK(sc);
	while (!(mbox_read_4(sc, REG_STATUS) & STATUS_EMPTY))
		if (bcm_mbox_read_msg(sc, &chan) == 0) {
			sc->have_message[chan] = 1;
			wakeup(&sc->have_message[chan]);
		}
	MBOX_UNLOCK(sc);
}