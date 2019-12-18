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
struct imx6_anatop_softc {int refosc_mhz; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
cpufreq_mhz_from_div(struct imx6_anatop_softc *sc, uint32_t corediv, 
    uint32_t plldiv)
{

	return ((sc->refosc_mhz * (plldiv / 2)) / (corediv + 1));
}