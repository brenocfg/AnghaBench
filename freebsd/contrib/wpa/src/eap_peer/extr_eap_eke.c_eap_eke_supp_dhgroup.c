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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ EAP_EKE_DHGROUP_EKE_14 ; 
 scalar_t__ EAP_EKE_DHGROUP_EKE_15 ; 
 scalar_t__ EAP_EKE_DHGROUP_EKE_16 ; 
 scalar_t__ EAP_EKE_DHGROUP_EKE_2 ; 
 scalar_t__ EAP_EKE_DHGROUP_EKE_5 ; 

__attribute__((used)) static int eap_eke_supp_dhgroup(u8 dhgroup)
{
	return dhgroup == EAP_EKE_DHGROUP_EKE_2 ||
		dhgroup == EAP_EKE_DHGROUP_EKE_5 ||
		dhgroup == EAP_EKE_DHGROUP_EKE_14 ||
		dhgroup == EAP_EKE_DHGROUP_EKE_15 ||
		dhgroup == EAP_EKE_DHGROUP_EKE_16;
}