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
#define  EAP_EKE_PRF_HMAC_SHA1 129 
#define  EAP_EKE_PRF_HMAC_SHA2_256 128 
 int SHA1_MAC_LEN ; 
 int SHA256_MAC_LEN ; 

__attribute__((used)) static int eap_eke_auth_len(u8 prf)
{
	switch (prf) {
	case EAP_EKE_PRF_HMAC_SHA1:
		return SHA1_MAC_LEN;
	case EAP_EKE_PRF_HMAC_SHA2_256:
		return SHA256_MAC_LEN;
	}

	return -1;
}