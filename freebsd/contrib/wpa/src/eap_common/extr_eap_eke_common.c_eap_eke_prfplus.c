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
 scalar_t__ EAP_EKE_PRF_HMAC_SHA1 ; 
 scalar_t__ EAP_EKE_PRF_HMAC_SHA2_256 ; 
 int eap_eke_prf_hmac_sha1 (scalar_t__ const*,size_t,scalar_t__ const*,size_t,scalar_t__*,size_t) ; 
 int eap_eke_prf_hmac_sha256 (scalar_t__ const*,size_t,scalar_t__ const*,size_t,scalar_t__*,size_t) ; 

__attribute__((used)) static int eap_eke_prfplus(u8 prf, const u8 *key, size_t key_len,
			   const u8 *data, size_t data_len, u8 *res, size_t len)
{
	if (prf == EAP_EKE_PRF_HMAC_SHA1)
		return eap_eke_prf_hmac_sha1(key, key_len, data, data_len, res,
					     len);
	if (prf == EAP_EKE_PRF_HMAC_SHA2_256)
		return eap_eke_prf_hmac_sha256(key, key_len, data, data_len,
					       res, len);
	return -1;
}