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
 scalar_t__ const EAP_EKE_DHGROUP_EKE_14 ; 
 scalar_t__ const EAP_EKE_DHGROUP_EKE_15 ; 
 scalar_t__ const EAP_EKE_DHGROUP_EKE_16 ; 
 scalar_t__ const EAP_EKE_ENCR_AES128_CBC ; 
 scalar_t__ const EAP_EKE_MAC_HMAC_SHA1 ; 
 scalar_t__ const EAP_EKE_MAC_HMAC_SHA2_256 ; 
 scalar_t__ const EAP_EKE_PRF_HMAC_SHA1 ; 
 scalar_t__ const EAP_EKE_PRF_HMAC_SHA2_256 ; 

__attribute__((used)) static int supported_proposal(const u8 *pos)
{
	if (pos[0] == EAP_EKE_DHGROUP_EKE_16 &&
	    pos[1] == EAP_EKE_ENCR_AES128_CBC &&
	    pos[2] == EAP_EKE_PRF_HMAC_SHA2_256 &&
	    pos[3] == EAP_EKE_MAC_HMAC_SHA2_256)
		return 1;

	if (pos[0] == EAP_EKE_DHGROUP_EKE_15 &&
	    pos[1] == EAP_EKE_ENCR_AES128_CBC &&
	    pos[2] == EAP_EKE_PRF_HMAC_SHA2_256 &&
	    pos[3] == EAP_EKE_MAC_HMAC_SHA2_256)
		return 1;

	if (pos[0] == EAP_EKE_DHGROUP_EKE_14 &&
	    pos[1] == EAP_EKE_ENCR_AES128_CBC &&
	    pos[2] == EAP_EKE_PRF_HMAC_SHA2_256 &&
	    pos[3] == EAP_EKE_MAC_HMAC_SHA2_256)
		return 1;

	if (pos[0] == EAP_EKE_DHGROUP_EKE_14 &&
	    pos[1] == EAP_EKE_ENCR_AES128_CBC &&
	    pos[2] == EAP_EKE_PRF_HMAC_SHA1 &&
	    pos[3] == EAP_EKE_MAC_HMAC_SHA1)
		return 1;

	return 0;
}