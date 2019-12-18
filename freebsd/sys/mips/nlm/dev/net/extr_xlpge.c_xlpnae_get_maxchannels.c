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
struct nlm_xlpnae_softc {int max_ports; TYPE_1__* portcfg; } ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ num_channels; } ;

/* Variables and functions */
 scalar_t__ UNKNOWN ; 

__attribute__((used)) static int
xlpnae_get_maxchannels(struct nlm_xlpnae_softc *sc)
{
	int maxchans = 0;
	int i;

	for (i = 0; i < sc->max_ports; i++) {
		if (sc->portcfg[i].type == UNKNOWN)
			continue;
		maxchans += sc->portcfg[i].num_channels;
	}

	return (maxchans);
}