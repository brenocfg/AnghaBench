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
struct creator_softc {int sc_fifo_cache; } ;

/* Variables and functions */
 int FBC_UCSR_FIFO_MASK ; 
 int /*<<< orphan*/  FFB_FBC ; 
 int /*<<< orphan*/  FFB_FBC_UCSR ; 
 int FFB_READ (struct creator_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
creator_ras_fifo_wait(struct creator_softc *sc, int n)
{
	int cache;

	cache = sc->sc_fifo_cache;
	while (cache < n)
		cache = (FFB_READ(sc, FFB_FBC, FFB_FBC_UCSR) &
		    FBC_UCSR_FIFO_MASK) - 8;
	sc->sc_fifo_cache = cache - n;
}