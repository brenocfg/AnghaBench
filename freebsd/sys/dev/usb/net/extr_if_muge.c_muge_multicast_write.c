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
struct muge_softc {int /*<<< orphan*/ ** sc_pfilter_table; int /*<<< orphan*/  sc_mchash_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_DP_SEL_RSEL_VLAN_DA_ ; 
 int /*<<< orphan*/  ETH_DP_SEL_VHF_HASH_LEN ; 
 int /*<<< orphan*/  ETH_DP_SEL_VHF_VLAN_LEN ; 
 int MUGE_NUM_PFILTER_ADDRS_ ; 
 int /*<<< orphan*/  PFILTER_HI (int) ; 
 int /*<<< orphan*/  PFILTER_LO (int) ; 
 int /*<<< orphan*/  lan78xx_dataport_write (struct muge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lan78xx_write_reg (struct muge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
muge_multicast_write(struct muge_softc *sc)
{
	int i, ret;
	lan78xx_dataport_write(sc, ETH_DP_SEL_RSEL_VLAN_DA_,
	    ETH_DP_SEL_VHF_VLAN_LEN, ETH_DP_SEL_VHF_HASH_LEN,
	    sc->sc_mchash_table);

	for (i = 1; i < MUGE_NUM_PFILTER_ADDRS_; i++) {
		ret = lan78xx_write_reg(sc, PFILTER_HI(i), 0);
		ret = lan78xx_write_reg(sc, PFILTER_LO(i),
		    sc->sc_pfilter_table[i][1]);
		ret = lan78xx_write_reg(sc, PFILTER_HI(i),
		    sc->sc_pfilter_table[i][0]);
	}
}