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
 int /*<<< orphan*/  R92C_AFE_PLL_CTRL ; 
 int R92C_AFE_XTAL_CTRL ; 
 int R92C_LDOHCI12_CTRL ; 
 int R92C_RF_CTRL ; 
 int R92C_RF_CTRL_EN ; 
 int R92C_RF_CTRL_RSTB ; 
 int R92C_RF_CTRL_SDMRSTB ; 
 int R92C_SYS_FUNC_EN ; 
 int R92C_SYS_FUNC_EN_BBRSTB ; 
 int R92C_SYS_FUNC_EN_BB_GLB_RST ; 
 int R92C_SYS_FUNC_EN_DIO_RF ; 
 int R92C_SYS_FUNC_EN_USBA ; 
 int R92C_SYS_FUNC_EN_USBD ; 
 int /*<<< orphan*/  r92c_init_bb_common (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_setbits_2 (struct rtwn_softc*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int,int) ; 
 int /*<<< orphan*/  rtwn_write_2 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r92cu_init_bb(struct rtwn_softc *sc)
{

	/* Enable BB and RF. */
	rtwn_setbits_2(sc, R92C_SYS_FUNC_EN, 0,
	    R92C_SYS_FUNC_EN_BBRSTB | R92C_SYS_FUNC_EN_BB_GLB_RST |
	    R92C_SYS_FUNC_EN_DIO_RF);

	rtwn_write_2(sc, R92C_AFE_PLL_CTRL, 0xdb83);

	rtwn_write_1(sc, R92C_RF_CTRL,
	    R92C_RF_CTRL_EN | R92C_RF_CTRL_RSTB | R92C_RF_CTRL_SDMRSTB);
	rtwn_write_1(sc, R92C_SYS_FUNC_EN,
	    R92C_SYS_FUNC_EN_USBA | R92C_SYS_FUNC_EN_USBD |
	    R92C_SYS_FUNC_EN_BB_GLB_RST | R92C_SYS_FUNC_EN_BBRSTB);

	rtwn_write_1(sc, R92C_LDOHCI12_CTRL, 0x0f);
	rtwn_write_1(sc, 0x15, 0xe9);
	rtwn_write_1(sc, R92C_AFE_XTAL_CTRL + 1, 0x80);

	r92c_init_bb_common(sc);
}