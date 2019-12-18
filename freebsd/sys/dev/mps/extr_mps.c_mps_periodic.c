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
struct mps_softc {int mps_flags; int /*<<< orphan*/  periodic; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_DOORBELL_OFFSET ; 
 int MPI2_IOC_STATE_FAULT ; 
 int MPI2_IOC_STATE_MASK ; 
 int /*<<< orphan*/  MPS_FAULT ; 
 int MPS_FLAGS_SHUTDOWN ; 
 int MPS_PERIODIC_DELAY ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct mps_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  mps_dprint (struct mps_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int mps_regread (struct mps_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_reinit (struct mps_softc*) ; 

__attribute__((used)) static void
mps_periodic(void *arg)
{
	struct mps_softc *sc;
	uint32_t db;

	sc = (struct mps_softc *)arg;
	if (sc->mps_flags & MPS_FLAGS_SHUTDOWN)
		return;

	db = mps_regread(sc, MPI2_DOORBELL_OFFSET);
	if ((db & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_FAULT) {
		mps_dprint(sc, MPS_FAULT, "IOC Fault 0x%08x, Resetting\n", db);
		mps_reinit(sc);
	}

	callout_reset(&sc->periodic, MPS_PERIODIC_DELAY * hz, mps_periodic, sc);
}