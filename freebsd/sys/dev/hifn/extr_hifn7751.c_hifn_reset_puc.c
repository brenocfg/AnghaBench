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
struct hifn_softc {int sc_flags; } ;

/* Variables and functions */
 int HIFN_0_PUCTRL ; 
 int HIFN_0_PUCTRL2 ; 
 int HIFN_IS_7956 ; 
 int /*<<< orphan*/  HIFN_PUCTRL_DMAENA ; 
 int /*<<< orphan*/  WRITE_REG_0 (struct hifn_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hifn_puc_wait (struct hifn_softc*) ; 

__attribute__((used)) static void
hifn_reset_puc(struct hifn_softc *sc)
{
	/* Reset processing unit */
	int reg = HIFN_0_PUCTRL;

	if (sc->sc_flags & HIFN_IS_7956) {
		reg = HIFN_0_PUCTRL2;
	}
	WRITE_REG_0(sc, reg, HIFN_PUCTRL_DMAENA);

	hifn_puc_wait(sc);
}