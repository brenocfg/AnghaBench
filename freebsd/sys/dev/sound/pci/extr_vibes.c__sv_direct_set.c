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
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sv_direct_get (struct sc_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_sv_direct_set(struct sc_info *sc, u_int8_t reg, u_int8_t val, int line)
{
	u_int8_t n;
	bus_space_write_1(sc->enh_st, sc->enh_sh, reg, val);

	n = sv_direct_get(sc, reg);
	if (n != val) {
		device_printf(sc->dev, "sv_direct_set register 0x%02x %d != %d from line %d\n", reg, n, val, line);
	}
}