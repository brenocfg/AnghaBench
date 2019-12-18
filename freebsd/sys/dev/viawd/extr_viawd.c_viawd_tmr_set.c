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
struct viawd_softc {unsigned int timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIAWD_MEM_COUNT ; 
 unsigned int VIAWD_MEM_COUNT_MAX ; 
 unsigned int VIAWD_MEM_COUNT_MIN ; 
 int /*<<< orphan*/  viawd_write_4 (struct viawd_softc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
viawd_tmr_set(struct viawd_softc *sc, unsigned int timeout)
{

	/* Keep value in range. */
	if (timeout < VIAWD_MEM_COUNT_MIN)
		timeout = VIAWD_MEM_COUNT_MIN;
	else if (timeout > VIAWD_MEM_COUNT_MAX)
		timeout = VIAWD_MEM_COUNT_MAX;

	viawd_write_4(sc, VIAWD_MEM_COUNT, timeout);
	sc->timeout = timeout;
}