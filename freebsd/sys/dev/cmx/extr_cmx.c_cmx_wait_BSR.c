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
typedef  int /*<<< orphan*/  uint8_t ;
struct cmx_softc {int timeout; scalar_t__ dying; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENXIO ; 
 int PCATCH ; 
 int PWAIT ; 
 int SPIN_COUNT ; 
 int WAIT_TICKS ; 
 scalar_t__ cmx_test_BSR (struct cmx_softc*,int /*<<< orphan*/ ,int) ; 
 int tsleep (struct cmx_softc*,int,char*,int) ; 

__attribute__((used)) static inline int
cmx_wait_BSR(struct cmx_softc *sc, uint8_t flags, int test)
{
	int rv;

	for (int i = 0; i < SPIN_COUNT; i++) {
		if (cmx_test_BSR(sc, flags, test))
			return 0;
	}

	for (int i = 0; i * WAIT_TICKS < sc->timeout; i++) {
		if (cmx_test_BSR(sc, flags, test))
			return 0;
		rv = tsleep(sc, PWAIT|PCATCH, "cmx", WAIT_TICKS);
		/*
		 * Currently, the only reason for waking up with
		 * rv == 0 is when we are detaching, in which
		 * case sc->dying is always 1.
		 */
		if (sc->dying)
			return ENXIO;
		if (rv != EAGAIN)
			return rv;
	}

	/* timeout */
	return EIO;
}