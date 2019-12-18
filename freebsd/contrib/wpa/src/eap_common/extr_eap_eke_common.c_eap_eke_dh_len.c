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
typedef  int u8 ;

/* Variables and functions */
#define  EAP_EKE_DHGROUP_EKE_14 132 
#define  EAP_EKE_DHGROUP_EKE_15 131 
#define  EAP_EKE_DHGROUP_EKE_16 130 
#define  EAP_EKE_DHGROUP_EKE_2 129 
#define  EAP_EKE_DHGROUP_EKE_5 128 

__attribute__((used)) static int eap_eke_dh_len(u8 group)
{
	switch (group) {
	case EAP_EKE_DHGROUP_EKE_2:
		return 128;
	case EAP_EKE_DHGROUP_EKE_5:
		return 192;
	case EAP_EKE_DHGROUP_EKE_14:
		return 256;
	case EAP_EKE_DHGROUP_EKE_15:
		return 384;
	case EAP_EKE_DHGROUP_EKE_16:
		return 512;
	}

	return -1;
}