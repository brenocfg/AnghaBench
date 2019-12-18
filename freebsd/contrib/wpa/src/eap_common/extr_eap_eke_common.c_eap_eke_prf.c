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
 int hmac_sha1_vector (scalar_t__ const*,size_t,size_t,scalar_t__ const**,size_t*,scalar_t__*) ; 
 int hmac_sha256_vector (scalar_t__ const*,size_t,size_t,scalar_t__ const**,size_t*,scalar_t__*) ; 

__attribute__((used)) static int eap_eke_prf(u8 prf, const u8 *key, size_t key_len, const u8 *data,
		       size_t data_len, const u8 *data2, size_t data2_len,
		       u8 *res)
{
	const u8 *addr[2];
	size_t len[2];
	size_t num_elem = 1;

	addr[0] = data;
	len[0] = data_len;
	if (data2) {
		num_elem++;
		addr[1] = data2;
		len[1] = data2_len;
	}

	if (prf == EAP_EKE_PRF_HMAC_SHA1)
		return hmac_sha1_vector(key, key_len, num_elem, addr, len, res);
	if (prf == EAP_EKE_PRF_HMAC_SHA2_256)
		return hmac_sha256_vector(key, key_len, num_elem, addr, len,
					  res);
	return -1;
}