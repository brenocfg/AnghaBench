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
struct ubsec_softc {scalar_t__ sc_nqchip; int /*<<< orphan*/  sc_qchip; } ;
struct ubsec_q {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIMPLEQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ubsec_q* SIMPLEQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIMPLEQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_next ; 
 int /*<<< orphan*/  ubsec_free_q (struct ubsec_softc*,struct ubsec_q*) ; 

__attribute__((used)) static void
ubsec_cleanchip(struct ubsec_softc *sc)
{
	struct ubsec_q *q;

	while (!SIMPLEQ_EMPTY(&sc->sc_qchip)) {
		q = SIMPLEQ_FIRST(&sc->sc_qchip);
		SIMPLEQ_REMOVE_HEAD(&sc->sc_qchip, q_next);
		ubsec_free_q(sc, q);
	}
	sc->sc_nqchip = 0;
}