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
struct TYPE_3__ {int cpuports_mask; } ;
typedef  TYPE_1__ e6000sw_softc_t ;

/* Variables and functions */

__attribute__((used)) static __inline bool
e6000sw_is_cpuport(e6000sw_softc_t *sc, int port)
{

	return ((sc->cpuports_mask & (1 << port)) ? true : false);
}