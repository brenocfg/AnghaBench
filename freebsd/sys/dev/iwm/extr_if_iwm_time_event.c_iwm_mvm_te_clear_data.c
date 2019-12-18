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
struct iwm_softc {int /*<<< orphan*/  sc_flags; scalar_t__ sc_time_event_end_ticks; scalar_t__ sc_time_event_duration; scalar_t__ sc_time_event_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_FLAG_TE_ACTIVE ; 

__attribute__((used)) static void
iwm_mvm_te_clear_data(struct iwm_softc *sc)
{
	sc->sc_time_event_uid = 0;
	sc->sc_time_event_duration = 0;
	sc->sc_time_event_end_ticks = 0;
	sc->sc_flags &= ~IWM_FLAG_TE_ACTIVE;
}