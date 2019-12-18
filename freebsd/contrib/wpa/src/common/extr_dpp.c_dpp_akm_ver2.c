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
 int DPP_AKM_PSK_SAE_DPP ; 
 int DPP_AKM_SAE_DPP ; 

int dpp_akm_ver2(enum dpp_akm akm)
{
	return akm == DPP_AKM_SAE_DPP || akm == DPP_AKM_PSK_SAE_DPP;
}