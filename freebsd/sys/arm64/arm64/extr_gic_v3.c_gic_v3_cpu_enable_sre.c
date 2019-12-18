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
typedef  int /*<<< orphan*/  u_int ;
struct gic_v3_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int ICC_SRE_EL1_SRE ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_SPECIALREG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icc_sre_el1 ; 
 int /*<<< orphan*/  isb () ; 

__attribute__((used)) static int
gic_v3_cpu_enable_sre(struct gic_v3_softc *sc)
{
	uint64_t sre;
	u_int cpuid;

	cpuid = PCPU_GET(cpuid);
	/*
	 * Set the SRE bit to enable access to GIC CPU interface
	 * via system registers.
	 */
	sre = READ_SPECIALREG(icc_sre_el1);
	sre |= ICC_SRE_EL1_SRE;
	WRITE_SPECIALREG(icc_sre_el1, sre);
	isb();
	/*
	 * Now ensure that the bit is set.
	 */
	sre = READ_SPECIALREG(icc_sre_el1);
	if ((sre & ICC_SRE_EL1_SRE) == 0) {
		/* We are done. This was disabled in EL2 */
		device_printf(sc->dev, "ERROR: CPU%u cannot enable CPU interface "
		    "via system registers\n", cpuid);
		return (ENXIO);
	} else if (bootverbose) {
		device_printf(sc->dev,
		    "CPU%u enabled CPU interface via system registers\n",
		    cpuid);
	}

	return (0);
}