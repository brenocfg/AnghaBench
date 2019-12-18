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
typedef  int /*<<< orphan*/  uint8_t ;
struct mpr_softc {int /*<<< orphan*/  mpr_log_eh; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_EVENT_LOG_DATA ; 
 int /*<<< orphan*/  MPI2_EVENT_LOG_ENTRY_ADDED ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpr_log_evt_handler ; 
 int /*<<< orphan*/  mpr_register_events (struct mpr_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpr_attach_log(struct mpr_softc *sc)
{
	uint8_t events[16];

	bzero(events, 16);
	setbit(events, MPI2_EVENT_LOG_DATA);
	setbit(events, MPI2_EVENT_LOG_ENTRY_ADDED);

	mpr_register_events(sc, events, mpr_log_evt_handler, NULL,
	    &sc->mpr_log_eh);

	return (0);
}