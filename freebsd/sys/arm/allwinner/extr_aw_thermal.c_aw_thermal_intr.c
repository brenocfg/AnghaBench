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
typedef  int uint32_t ;
struct aw_thermal_softc {int /*<<< orphan*/  cf_task; } ;
typedef  void* device_t ;

/* Variables and functions */
 int ALARM_INT_ALL ; 
 int /*<<< orphan*/  RB_POWEROFF ; 
 int RD4 (struct aw_thermal_softc*,int /*<<< orphan*/ ) ; 
 int SHUT_INT_ALL ; 
 int /*<<< orphan*/  THS_INTS ; 
 int /*<<< orphan*/  WR4 (struct aw_thermal_softc*,int /*<<< orphan*/ ,int) ; 
 struct aw_thermal_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 int /*<<< orphan*/  shutdown_nice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static void
aw_thermal_intr(void *arg)
{
	struct aw_thermal_softc *sc;
	device_t dev;
	uint32_t ints;

	dev = arg;
	sc = device_get_softc(dev);

	ints = RD4(sc, THS_INTS);
	WR4(sc, THS_INTS, ints);

	if ((ints & SHUT_INT_ALL) != 0) {
		device_printf(dev,
		    "WARNING - current temperature exceeds safe limits\n");
		shutdown_nice(RB_POWEROFF);
	}

	if ((ints & ALARM_INT_ALL) != 0)
		taskqueue_enqueue(taskqueue_thread, &sc->cf_task);
}