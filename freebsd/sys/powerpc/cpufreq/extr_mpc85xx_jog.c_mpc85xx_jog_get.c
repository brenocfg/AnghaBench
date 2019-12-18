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
struct mpc85xx_jog_softc {int /*<<< orphan*/  cpu; } ;
struct cf_setting {int /*<<< orphan*/  dev; int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int EINVAL ; 
 int /*<<< orphan*/  GUTS_PORPLLSR ; 
 int /*<<< orphan*/  MHZ ; 
 int /*<<< orphan*/  PMJCR_GET_CORE_MULT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccsr_read4 (int /*<<< orphan*/ ) ; 
 struct mpc85xx_jog_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpc85xx_get_system_clock () ; 

__attribute__((used)) static int
mpc85xx_jog_get(device_t dev, struct cf_setting *set)
{
	struct mpc85xx_jog_softc *sc;
	uint32_t pmjcr;
	uint32_t freq;

	if (set == NULL)
		return (EINVAL);

	sc = device_get_softc(dev);
	memset(set, CPUFREQ_VAL_UNKNOWN, sizeof(*set));

	pmjcr = ccsr_read4(GUTS_PORPLLSR);
	freq = PMJCR_GET_CORE_MULT(pmjcr, sc->cpu);
	freq *= mpc85xx_get_system_clock();
	freq /= MHZ;
	
	set->freq = freq;
	set->dev = dev;

	return (0);
}