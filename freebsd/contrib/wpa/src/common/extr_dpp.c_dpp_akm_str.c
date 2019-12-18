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
typedef  enum dpp_akm { ____Placeholder_dpp_akm } dpp_akm ;

/* Variables and functions */
#define  DPP_AKM_DPP 133 
#define  DPP_AKM_PSK 132 
#define  DPP_AKM_PSK_SAE 131 
#define  DPP_AKM_PSK_SAE_DPP 130 
#define  DPP_AKM_SAE 129 
#define  DPP_AKM_SAE_DPP 128 

const char * dpp_akm_str(enum dpp_akm akm)
{
	switch (akm) {
	case DPP_AKM_DPP:
		return "dpp";
	case DPP_AKM_PSK:
		return "psk";
	case DPP_AKM_SAE:
		return "sae";
	case DPP_AKM_PSK_SAE:
		return "psk+sae";
	case DPP_AKM_SAE_DPP:
		return "dpp+sae";
	case DPP_AKM_PSK_SAE_DPP:
		return "dpp+psk+sae";
	default:
		return "??";
	}
}