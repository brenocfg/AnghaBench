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
typedef  enum al_eth_lm_link_mode { ____Placeholder_al_eth_lm_link_mode } al_eth_lm_link_mode ;

/* Variables and functions */
#define  AL_ETH_LM_MODE_10G_DA 132 
#define  AL_ETH_LM_MODE_10G_OPTIC 131 
#define  AL_ETH_LM_MODE_1G 130 
#define  AL_ETH_LM_MODE_25G 129 
#define  AL_ETH_LM_MODE_DISCONNECTED 128 

const char *
al_eth_lm_mode_convert_to_str(enum al_eth_lm_link_mode val)
{

	switch (val) {
	case AL_ETH_LM_MODE_DISCONNECTED:
		return ("AL_ETH_LM_MODE_DISCONNECTED");
	case AL_ETH_LM_MODE_10G_OPTIC:
		return ("AL_ETH_LM_MODE_10G_OPTIC");
	case AL_ETH_LM_MODE_10G_DA:
		return ("AL_ETH_LM_MODE_10G_DA");
	case AL_ETH_LM_MODE_1G:
		return ("AL_ETH_LM_MODE_1G");
	case AL_ETH_LM_MODE_25G:
		return ("AL_ETH_LM_MODE_25G");
	}

	return ("N/A");
}