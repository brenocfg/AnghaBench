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
typedef  size_t uint8_t ;
typedef  int uint64_t ;
struct ichss_softc {TYPE_1__* sets; int /*<<< orphan*/  dev; int /*<<< orphan*/  ctrl_reg; int /*<<< orphan*/  bm_reg; } ;
struct cf_setting {int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int freq; } ;

/* Variables and functions */
 scalar_t__ CPUFREQ_CMP (int /*<<< orphan*/ ,int) ; 
 int CPUFREQ_VAL_UNKNOWN ; 
 int /*<<< orphan*/  DPRINT (char*,size_t) ; 
 int EINVAL ; 
 int ENXIO ; 
 size_t ICHSS_BM_DISABLE ; 
 size_t ICHSS_CTRL_BIT ; 
 size_t ICH_GET_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICH_SET_REG (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cpu_est_clockrate (int /*<<< orphan*/ ,int*) ; 
 struct ichss_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ichss_set(device_t dev, const struct cf_setting *set)
{
	struct ichss_softc *sc;
	uint8_t bmval, new_val, old_val, req_val;
	uint64_t rate;
	register_t regs;

	/* Look up appropriate bit value based on frequency. */
	sc = device_get_softc(dev);
	if (CPUFREQ_CMP(set->freq, sc->sets[0].freq))
		req_val = 0;
	else if (CPUFREQ_CMP(set->freq, sc->sets[1].freq))
		req_val = ICHSS_CTRL_BIT;
	else
		return (EINVAL);
	DPRINT("ichss: requested setting %d\n", req_val);

	/* Disable interrupts and get the other register contents. */
	regs = intr_disable();
	old_val = ICH_GET_REG(sc->ctrl_reg) & ~ICHSS_CTRL_BIT;

	/*
	 * Disable bus master arbitration, write the new value to the control
	 * register, and then re-enable bus master arbitration.
	 */
	bmval = ICH_GET_REG(sc->bm_reg) | ICHSS_BM_DISABLE;
	ICH_SET_REG(sc->bm_reg, bmval);
	ICH_SET_REG(sc->ctrl_reg, old_val | req_val);
	ICH_SET_REG(sc->bm_reg, bmval & ~ICHSS_BM_DISABLE);

	/* Get the new value and re-enable interrupts. */
	new_val = ICH_GET_REG(sc->ctrl_reg);
	intr_restore(regs);

	/* Check if the desired state was indeed selected. */
	if (req_val != (new_val & ICHSS_CTRL_BIT)) {
	    device_printf(sc->dev, "transition to %d failed\n", req_val);
	    return (ENXIO);
	}

	/* Re-initialize our cycle counter if we don't know this new state. */
	if (sc->sets[req_val].freq == CPUFREQ_VAL_UNKNOWN) {
		cpu_est_clockrate(0, &rate);
		sc->sets[req_val].freq = rate / 1000000;
		DPRINT("ichss: set calibrated new rate of %d\n",
		    sc->sets[req_val].freq);
	}

	return (0);
}