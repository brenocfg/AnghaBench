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
struct generic_pm_domain {int dummy; } ;
struct gdsc {scalar_t__ pwrsts; int flags; } ;

/* Variables and functions */
 int AON_RESET ; 
 int CLAMP_IO ; 
 int /*<<< orphan*/  GDSC_ON ; 
 int HW_CTRL ; 
 int PWRSTS_OFF ; 
 scalar_t__ PWRSTS_ON ; 
 int SW_RESET ; 
 struct gdsc* domain_to_gdsc (struct generic_pm_domain*) ; 
 int /*<<< orphan*/  gdsc_assert_reset (struct gdsc*) ; 
 int /*<<< orphan*/  gdsc_assert_reset_aon (struct gdsc*) ; 
 int /*<<< orphan*/  gdsc_deassert_clamp_io (struct gdsc*) ; 
 int gdsc_deassert_reset (struct gdsc*) ; 
 int /*<<< orphan*/  gdsc_force_mem_on (struct gdsc*) ; 
 int gdsc_hwctrl (struct gdsc*,int) ; 
 int gdsc_toggle_logic (struct gdsc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gdsc_enable(struct generic_pm_domain *domain)
{
	struct gdsc *sc = domain_to_gdsc(domain);
	int ret;

	if (sc->pwrsts == PWRSTS_ON)
		return gdsc_deassert_reset(sc);

	if (sc->flags & SW_RESET) {
		gdsc_assert_reset(sc);
		udelay(1);
		gdsc_deassert_reset(sc);
	}

	if (sc->flags & CLAMP_IO) {
		if (sc->flags & AON_RESET)
			gdsc_assert_reset_aon(sc);
		gdsc_deassert_clamp_io(sc);
	}

	ret = gdsc_toggle_logic(sc, GDSC_ON);
	if (ret)
		return ret;

	if (sc->pwrsts & PWRSTS_OFF)
		gdsc_force_mem_on(sc);

	/*
	 * If clocks to this power domain were already on, they will take an
	 * additional 4 clock cycles to re-enable after the power domain is
	 * enabled. Delay to account for this. A delay is also needed to ensure
	 * clocks are not enabled within 400ns of enabling power to the
	 * memories.
	 */
	udelay(1);

	/* Turn on HW trigger mode if supported */
	if (sc->flags & HW_CTRL) {
		ret = gdsc_hwctrl(sc, true);
		if (ret)
			return ret;
		/*
		 * Wait for the GDSC to go through a power down and
		 * up cycle.  In case a firmware ends up polling status
		 * bits for the gdsc, it might read an 'on' status before
		 * the GDSC can finish the power cycle.
		 * We wait 1us before returning to ensure the firmware
		 * can't immediately poll the status bits.
		 */
		udelay(1);
	}

	return 0;
}