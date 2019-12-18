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
 scalar_t__ EAP_EKE_MAC_HMAC_SHA1 ; 
 scalar_t__ EAP_EKE_MAC_HMAC_SHA2_256 ; 
 int /*<<< orphan*/  SHA1_MAC_LEN ; 
 int /*<<< orphan*/  SHA256_MAC_LEN ; 
 int hmac_sha1 (scalar_t__ const*,int /*<<< orphan*/ ,scalar_t__ const*,size_t,scalar_t__*) ; 
 int hmac_sha256 (scalar_t__ const*,int /*<<< orphan*/ ,scalar_t__ const*,size_t,scalar_t__*) ; 

__attribute__((used)) static int eap_eke_mac(u8 mac, const u8 *key, const u8 *data, size_t data_len,
		       u8 *res)
{
	if (mac == EAP_EKE_MAC_HMAC_SHA1)
		return hmac_sha1(key, SHA1_MAC_LEN, data, data_len, res);
	if (mac == EAP_EKE_MAC_HMAC_SHA2_256)
		return hmac_sha256(key, SHA256_MAC_LEN, data, data_len, res);
	return -1;
}