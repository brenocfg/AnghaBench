#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct openpic_softc {int /*<<< orphan*/ * sc_saved_vectors; int /*<<< orphan*/  sc_memr; TYPE_1__* sc_saved_timers; int /*<<< orphan*/ * sc_saved_prios; int /*<<< orphan*/ * sc_saved_ipis; int /*<<< orphan*/  sc_saved_config; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  tdst; int /*<<< orphan*/  tvec; int /*<<< orphan*/  tbase; int /*<<< orphan*/  tcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPENPIC_CONFIG ; 
 int /*<<< orphan*/  OPENPIC_IPI_VECTOR (int) ; 
 int OPENPIC_NIPIS ; 
 int /*<<< orphan*/  OPENPIC_PCPU_TPR (int) ; 
 int /*<<< orphan*/  OPENPIC_SRC_VECTOR (int) ; 
 int OPENPIC_SRC_VECTOR_COUNT ; 
 int /*<<< orphan*/  OPENPIC_TBASE (int) ; 
 int /*<<< orphan*/  OPENPIC_TCNT (int) ; 
 int /*<<< orphan*/  OPENPIC_TDST (int) ; 
 int OPENPIC_TIMERS ; 
 int /*<<< orphan*/  OPENPIC_TVEC (int) ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct openpic_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
openpic_resume(device_t dev)
{
    	struct openpic_softc *sc;
    	int i;

    	sc = device_get_softc(dev);

	sc->sc_saved_config = bus_read_4(sc->sc_memr, OPENPIC_CONFIG);
	for (i = 0; i < OPENPIC_NIPIS; i++) {
		bus_write_4(sc->sc_memr, OPENPIC_IPI_VECTOR(i), sc->sc_saved_ipis[i]);
	}

	for (i = 0; i < 4; i++) {
		bus_write_4(sc->sc_memr, OPENPIC_PCPU_TPR(i), sc->sc_saved_prios[i]);
	}

	for (i = 0; i < OPENPIC_TIMERS; i++) {
		bus_write_4(sc->sc_memr, OPENPIC_TCNT(i), sc->sc_saved_timers[i].tcnt);
		bus_write_4(sc->sc_memr, OPENPIC_TBASE(i), sc->sc_saved_timers[i].tbase);
		bus_write_4(sc->sc_memr, OPENPIC_TVEC(i), sc->sc_saved_timers[i].tvec);
		bus_write_4(sc->sc_memr, OPENPIC_TDST(i), sc->sc_saved_timers[i].tdst);
	}

	for (i = 0; i < OPENPIC_SRC_VECTOR_COUNT; i++)
		bus_write_4(sc->sc_memr, OPENPIC_SRC_VECTOR(i), sc->sc_saved_vectors[i]);

	return (0);
}