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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sc_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  enh_sh; int /*<<< orphan*/  enh_st; } ;

/* Variables and functions */
 int /*<<< orphan*/  SV_CM_DATA ; 
 int /*<<< orphan*/  SV_CM_INDEX ; 
 int /*<<< orphan*/  SV_CM_INDEX_MCE ; 
 int /*<<< orphan*/  SV_REG_ADC_PLLM ; 
 int /*<<< orphan*/  SV_REG_ANALOG_PWR ; 
 int /*<<< orphan*/  SV_REG_FORMAT ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sv_indirect_get (struct sc_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_sv_indirect_set(struct sc_info *sc, u_int8_t reg, u_int8_t val, int line)
{
	if (reg == SV_REG_FORMAT || reg == SV_REG_ANALOG_PWR)
		reg |= SV_CM_INDEX_MCE;

	bus_space_write_1(sc->enh_st, sc->enh_sh, SV_CM_INDEX, reg);
	bus_space_write_1(sc->enh_st, sc->enh_sh, SV_CM_DATA, val);

	reg &= ~SV_CM_INDEX_MCE;
	if (reg != SV_REG_ADC_PLLM) {
		u_int8_t n;
		n = sv_indirect_get(sc, reg);
		if (n != val) {
			device_printf(sc->dev, "sv_indirect_set register 0x%02x %d != %d line %d\n", reg, n, val, line);
		}
	}
}