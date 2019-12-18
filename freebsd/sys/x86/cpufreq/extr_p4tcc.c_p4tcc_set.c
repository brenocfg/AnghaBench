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
typedef  int uint64_t ;
struct p4tcc_softc {int lowest_val; int /*<<< orphan*/  auto_mode; } ;
struct cf_setting {int freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSR_THERM_CONTROL ; 
 int TCC_ENABLE_ONDEMAND ; 
 int TCC_NUM_SETTINGS ; 
 int TCC_REG_OFFSET ; 
 int /*<<< orphan*/  TRUE ; 
 struct p4tcc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
p4tcc_set(device_t dev, const struct cf_setting *set)
{
	struct p4tcc_softc *sc;
	uint64_t mask, msr;
	int val;

	if (set == NULL)
		return (EINVAL);
	sc = device_get_softc(dev);

	/*
	 * Validate requested state converts to a setting that is an integer
	 * from [sc->lowest_val .. TCC_NUM_SETTINGS].
	 */
	val = set->freq * TCC_NUM_SETTINGS / 10000;
	if (val * 10000 != set->freq * TCC_NUM_SETTINGS ||
	    val < sc->lowest_val || val > TCC_NUM_SETTINGS)
		return (EINVAL);

	/*
	 * Read the current register and mask off the old setting and
	 * On-Demand bit.  If the new val is < 100%, set it and the On-Demand
	 * bit, otherwise just return to Automatic mode.
	 */
	msr = rdmsr(MSR_THERM_CONTROL);
	mask = (TCC_NUM_SETTINGS - 1) << TCC_REG_OFFSET;
	msr &= ~(mask | TCC_ENABLE_ONDEMAND);
	if (val < TCC_NUM_SETTINGS)
		msr |= (val << TCC_REG_OFFSET) | TCC_ENABLE_ONDEMAND;
	wrmsr(MSR_THERM_CONTROL, msr);

	/*
	 * Record whether we're now in Automatic or On-Demand mode.  We have
	 * to cache this since there is no reliable way to check if TCC is in
	 * Automatic mode (i.e., at 100% or possibly 50%).  Reading bit 4 of
	 * the ACPI Thermal Monitor Control Register produces 0 no matter
	 * what the current mode.
	 */
	if (msr & TCC_ENABLE_ONDEMAND)
		sc->auto_mode = FALSE;
	else
		sc->auto_mode = TRUE;

	return (0);
}