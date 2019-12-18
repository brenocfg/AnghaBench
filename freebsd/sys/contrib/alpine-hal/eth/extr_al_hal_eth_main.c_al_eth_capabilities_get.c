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
struct al_hal_eth_adapter {int mac_mode; } ;
struct al_eth_capabilities {void* pfc; void* speed_10000_FD; void* eee; void* speed_1000_FD; void* speed_100_FD; void* speed_100_HD; void* speed_10_FD; void* speed_10_HD; void* speed_10000_HD; void* speed_1000_HD; } ;

/* Variables and functions */
#define  AL_ETH_MAC_MODE_10GbE_Serial 130 
#define  AL_ETH_MAC_MODE_RGMII 129 
#define  AL_ETH_MAC_MODE_SGMII 128 
 void* AL_FALSE ; 
 void* AL_TRUE ; 
 int EPERM ; 
 int /*<<< orphan*/  al_assert (struct al_eth_capabilities*) ; 
 int /*<<< orphan*/  al_err (char*,int) ; 

int al_eth_capabilities_get(struct al_hal_eth_adapter *adapter, struct al_eth_capabilities *caps)
{
	al_assert(caps);

	caps->speed_10_HD = AL_FALSE;
	caps->speed_10_FD = AL_FALSE;
	caps->speed_100_HD = AL_FALSE;
	caps->speed_100_FD = AL_FALSE;
	caps->speed_1000_HD = AL_FALSE;
	caps->speed_1000_FD = AL_FALSE;
	caps->speed_10000_HD = AL_FALSE;
	caps->speed_10000_FD = AL_FALSE;
	caps->pfc = AL_FALSE;
	caps->eee = AL_FALSE;

	switch (adapter->mac_mode) {
		case AL_ETH_MAC_MODE_RGMII:
		case AL_ETH_MAC_MODE_SGMII:
			caps->speed_10_HD = AL_TRUE;
			caps->speed_10_FD = AL_TRUE;
			caps->speed_100_HD = AL_TRUE;
			caps->speed_100_FD = AL_TRUE;
			caps->speed_1000_FD = AL_TRUE;
			caps->eee = AL_TRUE;
			break;
		case AL_ETH_MAC_MODE_10GbE_Serial:
			caps->speed_10000_FD = AL_TRUE;
			caps->pfc = AL_TRUE;
			break;
		default:
		al_err("Eth: unsupported MAC mode %d", adapter->mac_mode);
		return -EPERM;
	}
	return 0;
}