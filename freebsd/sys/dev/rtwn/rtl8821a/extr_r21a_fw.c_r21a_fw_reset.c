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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ R92C_RSV_CTRL ; 
 int /*<<< orphan*/  R92C_SYS_FUNC_EN ; 
 int /*<<< orphan*/  R92C_SYS_FUNC_EN_CPUEN ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  rtwn_setbits_1_shift (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
r21a_fw_reset(struct rtwn_softc *sc, int reason)
{

	/* Reset MCU IO wrapper. */
	rtwn_setbits_1(sc, R92C_RSV_CTRL, 0x02, 0);
	rtwn_setbits_1(sc, R92C_RSV_CTRL + 1, 0x01, 0);

	rtwn_setbits_1_shift(sc, R92C_SYS_FUNC_EN,
	    R92C_SYS_FUNC_EN_CPUEN, 0, 1);

	/* Enable MCU IO wrapper. */
	rtwn_setbits_1(sc, R92C_RSV_CTRL, 0x02, 0);
	rtwn_setbits_1(sc, R92C_RSV_CTRL + 1, 0, 0x01);

	rtwn_setbits_1_shift(sc, R92C_SYS_FUNC_EN,
	    0, R92C_SYS_FUNC_EN_CPUEN, 1);
}