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
struct apm_softc {scalar_t__ initialized; scalar_t__ always_halt_cpu; } ;

/* Variables and functions */
 struct apm_softc apm_softc ; 

__attribute__((used)) static void
apm_not_halt_cpu(void)
{
	struct apm_softc *sc = &apm_softc;

	if (sc == NULL || sc->initialized == 0)
		return;

	sc->always_halt_cpu = 0;

	return;
}