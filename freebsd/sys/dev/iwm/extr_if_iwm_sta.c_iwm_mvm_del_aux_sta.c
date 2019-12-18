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
struct TYPE_2__ {int /*<<< orphan*/  sta_id; } ;
struct iwm_softc {TYPE_1__ sc_aux_sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_MVM_STATION_COUNT ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void iwm_mvm_del_aux_sta(struct iwm_softc *sc)
{
	memset(&sc->sc_aux_sta, 0, sizeof(sc->sc_aux_sta));
	sc->sc_aux_sta.sta_id = IWM_MVM_STATION_COUNT;
}