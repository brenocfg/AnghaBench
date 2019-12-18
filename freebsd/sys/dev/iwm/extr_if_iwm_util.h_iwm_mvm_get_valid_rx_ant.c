#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int valid_rx_ant; } ;
struct iwm_softc {TYPE_2__ sc_fw; TYPE_1__* nvm_data; } ;
struct TYPE_3__ {int valid_rx_ant; } ;

/* Variables and functions */

__attribute__((used)) static inline uint8_t
iwm_mvm_get_valid_rx_ant(struct iwm_softc *sc)
{
	return sc->nvm_data && sc->nvm_data->valid_rx_ant ?
	       sc->sc_fw.valid_rx_ant & sc->nvm_data->valid_rx_ant :
	       sc->sc_fw.valid_rx_ant;
}