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
struct cs4231_softc {int sc_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs4231_power_reset (struct cs4231_softc*,int) ; 

__attribute__((used)) static int
cs4231_enable(struct cs4231_softc *sc, int how)
{
	cs4231_power_reset(sc, how);
	sc->sc_enabled = 1;
        return (0);
}