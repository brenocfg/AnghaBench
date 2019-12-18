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
struct saf1761_otg_softc {int* sc_host_async_busy_map; int* sc_host_intr_busy_map; int* sc_host_isoc_busy_map; scalar_t__ sc_xfer_complete; int /*<<< orphan*/  sc_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int,int) ; 
 int FILTER_HANDLED ; 
 int FILTER_SCHEDULE_THREAD ; 
 int SAF1761_DCINTERRUPT_THREAD_IRQ ; 
 int SAF1761_READ_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAF1761_WRITE_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SOTG_ATL_PTD_DONE_PTD ; 
 int /*<<< orphan*/  SOTG_DCINTERRUPT ; 
 int SOTG_DCINTERRUPT_IEPSOF ; 
 int /*<<< orphan*/  SOTG_HCINTERRUPT ; 
 int /*<<< orphan*/  SOTG_INT_PTD_DONE_PTD ; 
 int /*<<< orphan*/  SOTG_ISO_PTD_DONE_PTD ; 
 int /*<<< orphan*/  USB_BUS_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saf1761_otg_enable_psof (struct saf1761_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saf1761_otg_interrupt_poll_locked (struct saf1761_otg_softc*) ; 

int
saf1761_otg_filter_interrupt(void *arg)
{
	struct saf1761_otg_softc *sc = arg;
	int retval = FILTER_HANDLED;
	uint32_t hcstat;
	uint32_t status;

	USB_BUS_SPIN_LOCK(&sc->sc_bus);

	hcstat = SAF1761_READ_LE_4(sc, SOTG_HCINTERRUPT);
	/* acknowledge all host controller interrupts */
	SAF1761_WRITE_LE_4(sc, SOTG_HCINTERRUPT, hcstat);

	status = SAF1761_READ_LE_4(sc, SOTG_DCINTERRUPT);
	/* acknowledge all device controller interrupts */
	SAF1761_WRITE_LE_4(sc, SOTG_DCINTERRUPT,
	    status & ~SAF1761_DCINTERRUPT_THREAD_IRQ);

	(void) SAF1761_READ_LE_4(sc, SOTG_ATL_PTD_DONE_PTD);
	(void) SAF1761_READ_LE_4(sc, SOTG_INT_PTD_DONE_PTD);
	(void) SAF1761_READ_LE_4(sc, SOTG_ISO_PTD_DONE_PTD);

	DPRINTFN(9, "HCINTERRUPT=0x%08x DCINTERRUPT=0x%08x\n", hcstat, status);

	if (status & SOTG_DCINTERRUPT_IEPSOF) {
		if ((sc->sc_host_async_busy_map[1] | sc->sc_host_async_busy_map[0] |
		     sc->sc_host_intr_busy_map[1] | sc->sc_host_intr_busy_map[0] |
		     sc->sc_host_isoc_busy_map[1] | sc->sc_host_isoc_busy_map[0]) != 0) {
			/* busy waiting is active */
			retval = FILTER_SCHEDULE_THREAD;

			sc->sc_host_async_busy_map[1] = sc->sc_host_async_busy_map[0];
			sc->sc_host_async_busy_map[0] = 0;

			sc->sc_host_intr_busy_map[1] = sc->sc_host_intr_busy_map[0];
			sc->sc_host_intr_busy_map[0] = 0;

			sc->sc_host_isoc_busy_map[1] = sc->sc_host_isoc_busy_map[0];
			sc->sc_host_isoc_busy_map[0] = 0;
		} else {
			/* busy waiting is not active */
			saf1761_otg_enable_psof(sc, 0);
		}
	}

	if (status & SAF1761_DCINTERRUPT_THREAD_IRQ)
		retval = FILTER_SCHEDULE_THREAD;

	/* poll FIFOs, if any */
	saf1761_otg_interrupt_poll_locked(sc);

	if (sc->sc_xfer_complete != 0)
		retval = FILTER_SCHEDULE_THREAD;

	USB_BUS_SPIN_UNLOCK(&sc->sc_bus);

	return (retval);
}