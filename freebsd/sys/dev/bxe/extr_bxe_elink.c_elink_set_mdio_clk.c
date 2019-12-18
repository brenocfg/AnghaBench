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
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 int EMAC_MDIO_MODE_AUTO_POLL ; 
 int EMAC_MDIO_MODE_CLAUSE_45 ; 
 int EMAC_MDIO_MODE_CLOCK_CNT ; 
 long EMAC_MDIO_MODE_CLOCK_CNT_BITSHIFT ; 
 int EMAC_REG_EMAC_MDIO_MODE ; 
 int REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 scalar_t__ USES_WARPCORE (struct bxe_softc*) ; 

__attribute__((used)) static void elink_set_mdio_clk(struct bxe_softc *sc, uint32_t chip_id,
			       uint32_t emac_base)
{
	uint32_t new_mode, cur_mode;
	uint32_t clc_cnt;
	/* Set clause 45 mode, slow down the MDIO clock to 2.5MHz
	 * (a value of 49==0x31) and make sure that the AUTO poll is off
	 */
	cur_mode = REG_RD(sc, emac_base + EMAC_REG_EMAC_MDIO_MODE);

	if (USES_WARPCORE(sc))
		clc_cnt = 74L << EMAC_MDIO_MODE_CLOCK_CNT_BITSHIFT;
	else
		clc_cnt = 49L << EMAC_MDIO_MODE_CLOCK_CNT_BITSHIFT;

	if (((cur_mode & EMAC_MDIO_MODE_CLOCK_CNT) == clc_cnt) &&
	    (cur_mode & (EMAC_MDIO_MODE_CLAUSE_45)))
		return;

	new_mode = cur_mode &
		~(EMAC_MDIO_MODE_AUTO_POLL | EMAC_MDIO_MODE_CLOCK_CNT);
	new_mode |= clc_cnt;
	new_mode |= (EMAC_MDIO_MODE_CLAUSE_45);

	ELINK_DEBUG_P2(sc, "Changing emac_mode from 0x%x to 0x%x\n",
	   cur_mode, new_mode);
	REG_WR(sc, emac_base + EMAC_REG_EMAC_MDIO_MODE, new_mode);
	DELAY(40);
}