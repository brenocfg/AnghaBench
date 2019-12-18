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
struct iwm_softc {int dummy; } ;
struct iwm_rx_phy_info {int /*<<< orphan*/ * non_cfg_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_DEBUG_RECV ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 size_t IWM_RX_INFO_ENERGY_ANT_ABC_IDX ; 
 int IWM_RX_INFO_ENERGY_ANT_A_MSK ; 
 int IWM_RX_INFO_ENERGY_ANT_A_POS ; 
 int IWM_RX_INFO_ENERGY_ANT_B_MSK ; 
 int IWM_RX_INFO_ENERGY_ANT_B_POS ; 
 int IWM_RX_INFO_ENERGY_ANT_C_MSK ; 
 int IWM_RX_INFO_ENERGY_ANT_C_POS ; 
 int MAX (int,int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwm_mvm_rx_get_signal_strength(struct iwm_softc *sc,
    struct iwm_rx_phy_info *phy_info)
{
	int energy_a, energy_b, energy_c, max_energy;
	uint32_t val;

	val = le32toh(phy_info->non_cfg_phy[IWM_RX_INFO_ENERGY_ANT_ABC_IDX]);
	energy_a = (val & IWM_RX_INFO_ENERGY_ANT_A_MSK) >>
	    IWM_RX_INFO_ENERGY_ANT_A_POS;
	energy_a = energy_a ? -energy_a : -256;
	energy_b = (val & IWM_RX_INFO_ENERGY_ANT_B_MSK) >>
	    IWM_RX_INFO_ENERGY_ANT_B_POS;
	energy_b = energy_b ? -energy_b : -256;
	energy_c = (val & IWM_RX_INFO_ENERGY_ANT_C_MSK) >>
	    IWM_RX_INFO_ENERGY_ANT_C_POS;
	energy_c = energy_c ? -energy_c : -256;
	max_energy = MAX(energy_a, energy_b);
	max_energy = MAX(max_energy, energy_c);

	IWM_DPRINTF(sc, IWM_DEBUG_RECV,
	    "energy In A %d B %d C %d , and max %d\n",
	    energy_a, energy_b, energy_c, max_energy);

	return max_energy;
}