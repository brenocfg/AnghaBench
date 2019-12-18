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
struct ncr53c9x_softc {int sc_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  NCR_LOCK_ASSERT (struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 int ncr53c9x_cpb2stp (struct ncr53c9x_softc*,int) ; 

__attribute__((used)) static inline int
ncr53c9x_stp2cpb(struct ncr53c9x_softc *sc, int period)
{
	int v;

	NCR_LOCK_ASSERT(sc, MA_OWNED);

	v = (sc->sc_freq * period) / 250;
	if (ncr53c9x_cpb2stp(sc, v) < period)
		/* Correct round-down error. */
		v++;
	return (v);
}