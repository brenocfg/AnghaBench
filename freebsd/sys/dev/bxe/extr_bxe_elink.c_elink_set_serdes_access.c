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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ EMAC_REG_EMAC_MDIO_COMM ; 
 scalar_t__ GRCBASE_EMAC0 ; 
 scalar_t__ GRCBASE_EMAC1 ; 
 scalar_t__ NIG_REG_SERDES0_CTRL_MD_ST ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 

__attribute__((used)) static void elink_set_serdes_access(struct bxe_softc *sc, uint8_t port)
{
	uint32_t emac_base = (port) ? GRCBASE_EMAC1 : GRCBASE_EMAC0;

	/* Set Clause 22 */
	REG_WR(sc, NIG_REG_SERDES0_CTRL_MD_ST + port*0x10, 1);
	REG_WR(sc, emac_base + EMAC_REG_EMAC_MDIO_COMM, 0x245f8000);
	DELAY(500);
	REG_WR(sc, emac_base + EMAC_REG_EMAC_MDIO_COMM, 0x245d000f);
	DELAY(500);
	 /* Set Clause 45 */
	REG_WR(sc, NIG_REG_SERDES0_CTRL_MD_ST + port*0x10, 0);
}