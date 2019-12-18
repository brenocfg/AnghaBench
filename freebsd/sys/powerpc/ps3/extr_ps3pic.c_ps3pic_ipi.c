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
typedef  size_t u_int ;
struct ps3pic_softc {int /*<<< orphan*/ * sc_ipi_outlet; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ps3pic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv1_send_event_locally (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ps3pic_ipi(device_t dev, u_int cpu)
{
	struct ps3pic_softc *sc;
	sc = device_get_softc(dev);

	lv1_send_event_locally(sc->sc_ipi_outlet[cpu]);
}