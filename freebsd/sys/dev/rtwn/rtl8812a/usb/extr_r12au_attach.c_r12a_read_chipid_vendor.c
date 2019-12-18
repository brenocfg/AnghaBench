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
struct rtwn_softc {struct r12a_softc* sc_priv; } ;
struct r12a_softc {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R12A_CHIP_C_CUT ; 
 int /*<<< orphan*/  R92C_SYS_CFG_CHIP_VER_RTL ; 

__attribute__((used)) static void
r12a_read_chipid_vendor(struct rtwn_softc *sc, uint32_t reg_sys_cfg)
{
	struct r12a_softc *rs = sc->sc_priv;

	if (MS(reg_sys_cfg, R92C_SYS_CFG_CHIP_VER_RTL) == 1)
		rs->chip |= R12A_CHIP_C_CUT;
}