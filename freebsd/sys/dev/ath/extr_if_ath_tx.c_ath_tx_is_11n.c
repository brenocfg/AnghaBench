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
struct ath_softc {TYPE_1__* sc_ah; } ;
struct TYPE_2__ {int ah_magic; } ;

/* Variables and functions */

__attribute__((used)) static inline int
ath_tx_is_11n(struct ath_softc *sc)
{
	return ((sc->sc_ah->ah_magic == 0x20065416) ||
		    (sc->sc_ah->ah_magic == 0x19741014));
}