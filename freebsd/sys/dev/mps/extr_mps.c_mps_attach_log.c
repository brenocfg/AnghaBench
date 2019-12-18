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
typedef  int /*<<< orphan*/  u32 ;
struct mps_softc {int /*<<< orphan*/  mps_log_eh; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_EVENT_LOG_DATA ; 
 int /*<<< orphan*/  MPI2_EVENT_LOG_ENTRY_ADDED ; 
 int MPI2_EVENT_NOTIFY_EVENTMASK_WORDS ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mps_log_evt_handler ; 
 int /*<<< orphan*/  mps_register_events (struct mps_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mps_attach_log(struct mps_softc *sc)
{
	u32 events[MPI2_EVENT_NOTIFY_EVENTMASK_WORDS];

	bzero(events, 16);
	setbit(events, MPI2_EVENT_LOG_DATA);
	setbit(events, MPI2_EVENT_LOG_ENTRY_ADDED);

	mps_register_events(sc, events, mps_log_evt_handler, NULL,
	    &sc->mps_log_eh);

	return (0);
}