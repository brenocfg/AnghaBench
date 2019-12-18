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
struct rl_softc {int /*<<< orphan*/  rl_cfg5; int /*<<< orphan*/  rl_cfg3; int /*<<< orphan*/  rl_dev; } ;

/* Variables and functions */
 int CSR_READ_1 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 int RL_CFG3_WOL_LINK ; 
 int RL_CFG3_WOL_MAGIC ; 
 int RL_CFG5_WOL_BCAST ; 
 int RL_CFG5_WOL_LANWAKE ; 
 int RL_CFG5_WOL_MCAST ; 
 int RL_CFG5_WOL_UCAST ; 
 int /*<<< orphan*/  RL_EECMD ; 
 int RL_EEMODE_OFF ; 
 int RL_EE_MODE ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
re_clrwol(struct rl_softc *sc)
{
	int			pmc;
	uint8_t			v;

	RL_LOCK_ASSERT(sc);

	if (pci_find_cap(sc->rl_dev, PCIY_PMG, &pmc) != 0)
		return;

	/* Enable config register write. */
	CSR_WRITE_1(sc, RL_EECMD, RL_EE_MODE);

	v = CSR_READ_1(sc, sc->rl_cfg3);
	v &= ~(RL_CFG3_WOL_LINK | RL_CFG3_WOL_MAGIC);
	CSR_WRITE_1(sc, sc->rl_cfg3, v);

	/* Config register write done. */
	CSR_WRITE_1(sc, RL_EECMD, RL_EEMODE_OFF);

	v = CSR_READ_1(sc, sc->rl_cfg5);
	v &= ~(RL_CFG5_WOL_BCAST | RL_CFG5_WOL_MCAST | RL_CFG5_WOL_UCAST);
	v &= ~RL_CFG5_WOL_LANWAKE;
	CSR_WRITE_1(sc, sc->rl_cfg5, v);
}