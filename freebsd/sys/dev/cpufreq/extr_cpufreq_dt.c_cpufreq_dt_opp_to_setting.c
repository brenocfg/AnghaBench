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
struct cpufreq_dt_softc {int dummy; } ;
struct cpufreq_dt_opp {int freq; int uvolt_target; int /*<<< orphan*/  clk_latency; } ;
struct cf_setting {int freq; int volts; int /*<<< orphan*/  dev; int /*<<< orphan*/  lat; int /*<<< orphan*/  power; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 struct cpufreq_dt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cpufreq_dt_opp_to_setting(device_t dev, const struct cpufreq_dt_opp *opp,
    struct cf_setting *set)
{
	struct cpufreq_dt_softc *sc;

	sc = device_get_softc(dev);

	memset(set, 0, sizeof(*set));
	set->freq = opp->freq / 1000000;
	set->volts = opp->uvolt_target / 1000;
	set->power = CPUFREQ_VAL_UNKNOWN;
	set->lat = opp->clk_latency;
	set->dev = dev;
}