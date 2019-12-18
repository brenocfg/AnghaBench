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
struct p4tcc_softc {void* set_count; void* lowest_val; int /*<<< orphan*/  auto_mode; int /*<<< orphan*/  dev; } ;
struct cf_setting {int freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 void* TCC_NUM_SETTINGS ; 
 int /*<<< orphan*/  TRUE ; 
 int cpu_id ; 
 int /*<<< orphan*/  cpufreq_register (int /*<<< orphan*/ ) ; 
 struct p4tcc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p4tcc_set (int /*<<< orphan*/ ,struct cf_setting*) ; 

__attribute__((used)) static int
p4tcc_attach(device_t dev)
{
	struct p4tcc_softc *sc;
	struct cf_setting set;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->set_count = TCC_NUM_SETTINGS;

	/*
	 * On boot, the TCC is usually in Automatic mode where reading the
	 * current performance level is likely to produce bogus results.
	 * We record that state here and don't trust the contents of the
	 * status MSR until we've set it ourselves.
	 */
	sc->auto_mode = TRUE;

	/*
	 * XXX: After a cursory glance at various Intel specification
	 * XXX: updates it seems like these tests for errata is bogus.
	 * XXX: As far as I can tell, the failure mode is benign, in
	 * XXX: that cpus with no errata will have their bottom two
	 * XXX: STPCLK# rates disabled, so rather than waste more time
	 * XXX: hunting down intel docs, just document it and punt. /phk
	 */
	switch (cpu_id & 0xff) {
	case 0x22:
	case 0x24:
	case 0x25:
	case 0x27:
	case 0x29:
		/*
		 * These CPU models hang when set to 12.5%.
		 * See Errata O50, P44, and Z21.
		 */
		sc->set_count -= 1;
		break;
	case 0x07:	/* errata N44 and P18 */
	case 0x0a:
	case 0x12:
	case 0x13:
	case 0x62:	/* Pentium D B1: errata AA21 */
	case 0x64:	/* Pentium D C1: errata AA21 */
	case 0x65:	/* Pentium D D0: errata AA21 */
		/*
		 * These CPU models hang when set to 12.5% or 25%.
		 * See Errata N44, P18l and AA21.
		 */
		sc->set_count -= 2;
		break;
	}
	sc->lowest_val = TCC_NUM_SETTINGS - sc->set_count + 1;

	/*
	 * Before we finish attach, switch to 100%.  It's possible the BIOS
	 * set us to a lower rate.  The user can override this after boot.
	 */
	set.freq = 10000;
	p4tcc_set(dev, &set);

	cpufreq_register(dev);
	return (0);
}