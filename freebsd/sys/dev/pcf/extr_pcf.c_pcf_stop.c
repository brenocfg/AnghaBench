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
struct pcf_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pcf_softc* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCF_LOCK (struct pcf_softc*) ; 
 int /*<<< orphan*/  PCF_UNLOCK (struct pcf_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcf_stop_locked (struct pcf_softc*) ; 

int
pcf_stop(device_t dev)
{
	struct pcf_softc *sc = DEVTOSOFTC(dev);

#ifdef PCFDEBUG
	device_printf(dev, " >> stop\n");
#endif
	PCF_LOCK(sc);
	pcf_stop_locked(sc);
	PCF_UNLOCK(sc);

	return (0);
}