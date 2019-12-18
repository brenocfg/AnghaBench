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
struct iwm_softc {TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ mqrx_supported; } ;

/* Variables and functions */
 int iwm_nic_rx_legacy_init (struct iwm_softc*) ; 
 int iwm_nic_rx_mq_init (struct iwm_softc*) ; 

__attribute__((used)) static int
iwm_nic_rx_init(struct iwm_softc *sc)
{
	if (sc->cfg->mqrx_supported)
		return iwm_nic_rx_mq_init(sc);
	else
		return iwm_nic_rx_legacy_init(sc);
}