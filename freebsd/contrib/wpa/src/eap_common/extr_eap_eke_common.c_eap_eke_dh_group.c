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
struct dh_group {int dummy; } ;

/* Variables and functions */
#define  EAP_EKE_DHGROUP_EKE_14 132 
#define  EAP_EKE_DHGROUP_EKE_15 131 
#define  EAP_EKE_DHGROUP_EKE_16 130 
#define  EAP_EKE_DHGROUP_EKE_2 129 
#define  EAP_EKE_DHGROUP_EKE_5 128 
 struct dh_group const* dh_groups_get (int) ; 

__attribute__((used)) static const struct dh_group * eap_eke_dh_group(u8 group)
{
	switch (group) {
	case EAP_EKE_DHGROUP_EKE_2:
		return dh_groups_get(2);
	case EAP_EKE_DHGROUP_EKE_5:
		return dh_groups_get(5);
	case EAP_EKE_DHGROUP_EKE_14:
		return dh_groups_get(14);
	case EAP_EKE_DHGROUP_EKE_15:
		return dh_groups_get(15);
	case EAP_EKE_DHGROUP_EKE_16:
		return dh_groups_get(16);
	}

	return NULL;
}