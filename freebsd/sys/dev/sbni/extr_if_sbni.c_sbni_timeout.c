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
typedef  int u_char ;
struct TYPE_2__ {int /*<<< orphan*/  timeout_number; } ;
struct sbni_softc {int /*<<< orphan*/  wch; int /*<<< orphan*/  csr1; scalar_t__ delta_rxl; TYPE_1__ in_stats; scalar_t__ timer_ticks; } ;

/* Variables and functions */
 int BU_EMP ; 
 int /*<<< orphan*/  CSR0 ; 
 int /*<<< orphan*/  CSR1 ; 
 int PR_RES ; 
 int RC_CHK ; 
 int RC_RDY ; 
 int /*<<< orphan*/  SBNI_ASSERT_LOCKED (struct sbni_softc*) ; 
 int SBNI_HZ ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct sbni_softc*) ; 
 int hz ; 
 int sbni_inb (struct sbni_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbni_outb (struct sbni_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timeout_change_level (struct sbni_softc*) ; 

__attribute__((used)) static void
sbni_timeout(void *xsc)
{
	struct sbni_softc *sc;
	u_char csr0;

	sc = (struct sbni_softc *)xsc;
	SBNI_ASSERT_LOCKED(sc);

	csr0 = sbni_inb(sc, CSR0);
	if (csr0 & RC_CHK) {

		if (sc->timer_ticks) {
			if (csr0 & (RC_RDY | BU_EMP))
				/* receiving not active */
				sc->timer_ticks--;
		} else {
			sc->in_stats.timeout_number++;
			if (sc->delta_rxl)
				timeout_change_level(sc);

			sbni_outb(sc, CSR1, *(u_char *)&sc->csr1 | PR_RES);
			csr0 = sbni_inb(sc, CSR0);
		}
	}

	sbni_outb(sc, CSR0, csr0 | RC_CHK);
	callout_reset(&sc->wch, hz/SBNI_HZ, sbni_timeout, sc);
}