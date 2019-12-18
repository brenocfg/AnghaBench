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
struct cbb_softc {int /*<<< orphan*/  irq_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cbb_route_interrupt(device_t pcib, device_t dev, int pin)
{
	struct cbb_softc *sc = (struct cbb_softc *)device_get_softc(pcib);

	return (rman_get_start(sc->irq_res));
}