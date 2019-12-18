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
typedef  int /*<<< orphan*/  uint32_t ;
struct imx6_anatop_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_mhz_from_div (struct imx6_anatop_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_mhz_to_div (struct imx6_anatop_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint32_t
cpufreq_actual_mhz(struct imx6_anatop_softc *sc, uint32_t cpu_mhz)
{
	uint32_t corediv, plldiv;

	cpufreq_mhz_to_div(sc, cpu_mhz, &corediv, &plldiv);
	return (cpufreq_mhz_from_div(sc, corediv, plldiv));
}