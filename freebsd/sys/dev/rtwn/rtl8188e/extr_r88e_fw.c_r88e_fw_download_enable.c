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
 scalar_t__ R92C_MCUFWDL ; 
 int /*<<< orphan*/  R92C_MCUFWDL_EN ; 
 int /*<<< orphan*/  R92C_MCUFWDL_ROM_DLEN ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_setbits_1_shift (struct rtwn_softc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

void
r88e_fw_download_enable(struct rtwn_softc *sc, int enable)
{
	if (enable) {
		/* MCU firmware download enable. */
		rtwn_setbits_1(sc, R92C_MCUFWDL, 0, R92C_MCUFWDL_EN);
		/* 8051 reset. */
		rtwn_setbits_1_shift(sc, R92C_MCUFWDL, R92C_MCUFWDL_ROM_DLEN,
		    0, 2);
	} else {
		/* MCU download disable. */
		rtwn_setbits_1(sc, R92C_MCUFWDL, R92C_MCUFWDL_EN, 0);
		/* Reserved for f/w extension. */
		rtwn_write_1(sc, R92C_MCUFWDL + 1, 0);
	}
}