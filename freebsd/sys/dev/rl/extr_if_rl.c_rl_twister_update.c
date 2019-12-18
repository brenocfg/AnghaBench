#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  TYPE_1__ uint32_t ;
typedef  int uint16_t ;
struct rl_softc {int rl_twister; int rl_twist_row; size_t rl_twist_col; } ;

/* Variables and functions */
#define  CHK_LINK 133 
 int CSR_READ_2 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct rl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct rl_softc*,int /*<<< orphan*/ ,TYPE_1__ const) ; 
#define  DONE 132 
#define  FIND_ROW 131 
#define  RECHK_LONG 130 
#define  RETUNE 129 
 int /*<<< orphan*/  RL_CSCFG ; 
 int /*<<< orphan*/  RL_CSCFG_LINK_DOWN_CMD ; 
 int /*<<< orphan*/  RL_CSCFG_LINK_DOWN_OFF_CMD ; 
 int RL_CSCFG_LINK_OK ; 
 int RL_CSCFG_ROW1 ; 
 int RL_CSCFG_ROW2 ; 
 int RL_CSCFG_ROW3 ; 
 int RL_CSCFG_STATUS ; 
 int /*<<< orphan*/  RL_NWAYTST ; 
 TYPE_1__ const RL_NWAYTST_CBL_TEST ; 
 TYPE_1__ const RL_NWAYTST_RESET ; 
 int /*<<< orphan*/  RL_PARA78 ; 
 TYPE_1__ const RL_PARA78_DEF ; 
 int /*<<< orphan*/  RL_PARA7C ; 
 TYPE_1__ const RL_PARA7C_DEF ; 
 TYPE_1__ const RL_PARA7C_RETUNE ; 
#define  SET_PARAM 128 

__attribute__((used)) static void
rl_twister_update(struct rl_softc *sc)
{
	uint16_t linktest;
	/*
	 * Table provided by RealTek (Kinston <shangh@realtek.com.tw>) for
	 * Linux driver.  Values undocumented otherwise.
	 */
	static const uint32_t param[4][4] = {
		{0xcb39de43, 0xcb39ce43, 0xfb38de03, 0xcb38de43},
		{0xcb39de43, 0xcb39ce43, 0xcb39ce83, 0xcb39ce83},
		{0xcb39de43, 0xcb39ce43, 0xcb39ce83, 0xcb39ce83},
		{0xbb39de43, 0xbb39ce43, 0xbb39ce83, 0xbb39ce83}
	};

	/*
	 * Tune the so-called twister registers of the RTL8139.  These
	 * are used to compensate for impedance mismatches.  The
	 * method for tuning these registers is undocumented and the
	 * following procedure is collected from public sources.
	 */
	switch (sc->rl_twister)
	{
	case CHK_LINK:
		/*
		 * If we have a sufficient link, then we can proceed in
		 * the state machine to the next stage.  If not, then
		 * disable further tuning after writing sane defaults.
		 */
		if (CSR_READ_2(sc, RL_CSCFG) & RL_CSCFG_LINK_OK) {
			CSR_WRITE_2(sc, RL_CSCFG, RL_CSCFG_LINK_DOWN_OFF_CMD);
			sc->rl_twister = FIND_ROW;
		} else {
			CSR_WRITE_2(sc, RL_CSCFG, RL_CSCFG_LINK_DOWN_CMD);
			CSR_WRITE_4(sc, RL_NWAYTST, RL_NWAYTST_CBL_TEST);
			CSR_WRITE_4(sc, RL_PARA78, RL_PARA78_DEF);
			CSR_WRITE_4(sc, RL_PARA7C, RL_PARA7C_DEF);
			sc->rl_twister = DONE;
		}
		break;
	case FIND_ROW:
		/*
		 * Read how long it took to see the echo to find the tuning
		 * row to use.
		 */
		linktest = CSR_READ_2(sc, RL_CSCFG) & RL_CSCFG_STATUS;
		if (linktest == RL_CSCFG_ROW3)
			sc->rl_twist_row = 3;
		else if (linktest == RL_CSCFG_ROW2)
			sc->rl_twist_row = 2;
		else if (linktest == RL_CSCFG_ROW1)
			sc->rl_twist_row = 1;
		else
			sc->rl_twist_row = 0;
		sc->rl_twist_col = 0;
		sc->rl_twister = SET_PARAM;
		break;
	case SET_PARAM:
		if (sc->rl_twist_col == 0)
			CSR_WRITE_4(sc, RL_NWAYTST, RL_NWAYTST_RESET);
		CSR_WRITE_4(sc, RL_PARA7C,
		    param[sc->rl_twist_row][sc->rl_twist_col]);
		if (++sc->rl_twist_col == 4) {
			if (sc->rl_twist_row == 3)
				sc->rl_twister = RECHK_LONG;
			else
				sc->rl_twister = DONE;
		}
		break;
	case RECHK_LONG:
		/*
		 * For long cables, we have to double check to make sure we
		 * don't mistune.
		 */
		linktest = CSR_READ_2(sc, RL_CSCFG) & RL_CSCFG_STATUS;
		if (linktest == RL_CSCFG_ROW3)
			sc->rl_twister = DONE;
		else {
			CSR_WRITE_4(sc, RL_PARA7C, RL_PARA7C_RETUNE);
			sc->rl_twister = RETUNE;
		}
		break;
	case RETUNE:
		/* Retune for a shorter cable (try column 2) */
		CSR_WRITE_4(sc, RL_NWAYTST, RL_NWAYTST_CBL_TEST);
		CSR_WRITE_4(sc, RL_PARA78, RL_PARA78_DEF);
		CSR_WRITE_4(sc, RL_PARA7C, RL_PARA7C_DEF);
		CSR_WRITE_4(sc, RL_NWAYTST, RL_NWAYTST_RESET);
		sc->rl_twist_row--;
		sc->rl_twist_col = 0;
		sc->rl_twister = SET_PARAM;
		break;

	case DONE:
		break;
	}
	
}