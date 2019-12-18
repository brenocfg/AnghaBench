#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int64_t ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  void* bus_space_handle_t ;
struct TYPE_7__ {scalar_t__ max_qcount; scalar_t__ qcount; scalar_t__ call_count; scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_6__ {scalar_t__ max_qcount; scalar_t__ qcount; scalar_t__ call_count; scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_8__ {scalar_t__ ioh0; int command_byte; int retry; int /*<<< orphan*/  quirks; void* ioh1; int /*<<< orphan*/  iot; TYPE_2__ aux; TYPE_1__ kbd; void* aux_mux_enabled; void* lock; scalar_t__ command_mask; } ;
typedef  TYPE_3__ atkbdc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 void* FALSE ; 
 int KBDD_DELAYTIME ; 
 int /*<<< orphan*/  atkbdc_getquirks () ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int rdtsc () ; 
 int /*<<< orphan*/  read_status (TYPE_3__*) ; 

__attribute__((used)) static int
atkbdc_setup(atkbdc_softc_t *sc, bus_space_tag_t tag, bus_space_handle_t h0,
	     bus_space_handle_t h1)
{
#if defined(__amd64__)
	u_int64_t tscval[3], read_delay;
	register_t flags;
#endif

	if (sc->ioh0 == 0) {	/* XXX */
	    sc->command_byte = -1;
	    sc->command_mask = 0;
	    sc->lock = FALSE;
	    sc->kbd.head = sc->kbd.tail = 0;
	    sc->aux.head = sc->aux.tail = 0;
	    sc->aux_mux_enabled = FALSE;
#if KBDIO_DEBUG >= 2
	    sc->kbd.call_count = 0;
	    sc->kbd.qcount = sc->kbd.max_qcount = 0;
	    sc->aux.call_count = 0;
	    sc->aux.qcount = sc->aux.max_qcount = 0;
#endif
	}
	sc->iot = tag;
	sc->ioh0 = h0;
	sc->ioh1 = h1;

#if defined(__amd64__)
	/*
	 * On certain chipsets AT keyboard controller isn't present and is
	 * emulated by BIOS using SMI interrupt. On those chipsets reading
	 * from the status port may be thousand times slower than usually.
	 * Sometimes this emilation is not working properly resulting in
	 * commands timing our and since we assume that inb() operation 
	 * takes very little time to complete we need to adjust number of
	 * retries to keep waiting time within a designed limits (100ms).
	 * Measure time it takes to make read_status() call and adjust
	 * number of retries accordingly.
	 */
	flags = intr_disable();
	tscval[0] = rdtsc();
	read_status(sc);
	tscval[1] = rdtsc();
	DELAY(1000);
	tscval[2] = rdtsc();
	intr_restore(flags);
	read_delay = tscval[1] - tscval[0];
	read_delay /= (tscval[2] - tscval[1]) / 1000;
	sc->retry = 100000 / ((KBDD_DELAYTIME * 2) + read_delay);
#else
	sc->retry = 5000;
#endif
	sc->quirks = atkbdc_getquirks();

	return 0;
}