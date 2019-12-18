#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int fixed_mask; int cpuports_mask; } ;
typedef  TYPE_1__ e6000sw_softc_t ;

/* Variables and functions */

__attribute__((used)) static __inline bool
e6000sw_is_phyport(e6000sw_softc_t *sc, int port)
{
	uint32_t phy_mask;
	phy_mask = ~(sc->fixed_mask | sc->cpuports_mask);

	return ((phy_mask & (1 << port)) ? true : false);
}