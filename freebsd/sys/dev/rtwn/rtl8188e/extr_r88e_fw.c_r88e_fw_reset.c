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
typedef  int uint16_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_SYS_FUNC_EN ; 
 int R92C_SYS_FUNC_EN_CPUEN ; 
 int RTWN_FW_RESET_SHUTDOWN ; 
 int rtwn_read_2 (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_2 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r88e_fw_reset(struct rtwn_softc *sc, int reason)
{
	uint16_t reg;

	reg = rtwn_read_2(sc, R92C_SYS_FUNC_EN);
	rtwn_write_2(sc, R92C_SYS_FUNC_EN, reg & ~R92C_SYS_FUNC_EN_CPUEN);

	if (reason != RTWN_FW_RESET_SHUTDOWN) {
		rtwn_write_2(sc, R92C_SYS_FUNC_EN,
		    reg | R92C_SYS_FUNC_EN_CPUEN);
	}
}