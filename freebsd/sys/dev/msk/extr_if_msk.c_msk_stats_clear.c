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
typedef  int uint16_t ;
struct msk_softc {int dummy; } ;
struct msk_if_softc {int /*<<< orphan*/  msk_port; struct msk_softc* msk_softc; } ;

/* Variables and functions */
 int GMAC_READ_2 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMAC_WRITE_2 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int GM_PAR_MIB_CLR ; 
 int /*<<< orphan*/  GM_PHY_ADDR ; 
 int GM_RXF_UC_OK ; 
 int GM_TXE_FIFO_UR ; 
 int /*<<< orphan*/  MSK_IF_LOCK_ASSERT (struct msk_if_softc*) ; 
 int /*<<< orphan*/  MSK_READ_MIB32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
msk_stats_clear(struct msk_if_softc *sc_if)
{
	struct msk_softc *sc;
	uint32_t reg;
	uint16_t gmac;
	int i;

	MSK_IF_LOCK_ASSERT(sc_if);

	sc = sc_if->msk_softc;
	/* Set MIB Clear Counter Mode. */
	gmac = GMAC_READ_2(sc, sc_if->msk_port, GM_PHY_ADDR);
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_PHY_ADDR, gmac | GM_PAR_MIB_CLR);
	/* Read all MIB Counters with Clear Mode set. */
	for (i = GM_RXF_UC_OK; i <= GM_TXE_FIFO_UR; i += sizeof(uint32_t))
		reg = MSK_READ_MIB32(sc_if->msk_port, i);
	/* Clear MIB Clear Counter Mode. */
	gmac &= ~GM_PAR_MIB_CLR;
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_PHY_ADDR, gmac);
}