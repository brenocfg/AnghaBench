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
struct creator_softc {int sc_pmask_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  FFB_FBC ; 
 int /*<<< orphan*/  FFB_FBC_PMASK ; 
 int /*<<< orphan*/  FFB_WRITE (struct creator_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  creator_ras_fifo_wait (struct creator_softc*,int) ; 
 int /*<<< orphan*/  creator_ras_wait (struct creator_softc*) ; 

__attribute__((used)) static inline void
creator_ras_setpmask(struct creator_softc *sc, int pmask)
{

	if (pmask == sc->sc_pmask_cache)
		return;
	sc->sc_pmask_cache = pmask;
	creator_ras_fifo_wait(sc, 1);
	FFB_WRITE(sc, FFB_FBC, FFB_FBC_PMASK, pmask);
	creator_ras_wait(sc);
}