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
struct bwn_mac {int /*<<< orphan*/  mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_ERRPRINTF (int /*<<< orphan*/ ,char*,int) ; 
 int BWN_PHYROUTE_EXT_GPHY ; 
 int BWN_PHYROUTE_MASK ; 
 int BWN_PHYROUTE_OFDM_GPHY ; 

__attribute__((used)) static inline void check_phyreg(struct bwn_mac *mac, uint16_t offset)
{
#ifdef	BWN_DEBUG
	if ((offset & BWN_PHYROUTE_MASK) == BWN_PHYROUTE_OFDM_GPHY) {
		/* OFDM registers are onnly available on A/G-PHYs */
		BWN_ERRPRINTF(mac->mac_sc, "Invalid OFDM PHY access at "
		       "0x%04X on N-PHY\n", offset);
	}
	if ((offset & BWN_PHYROUTE_MASK) == BWN_PHYROUTE_EXT_GPHY) {
		/* Ext-G registers are only available on G-PHYs */
		BWN_ERRPRINTF(mac->mac_sc, "Invalid EXT-G PHY access at "
		       "0x%04X on N-PHY\n", offset);
	}
#endif /* BWN_DEBUG */
}