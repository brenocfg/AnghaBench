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
 int AES_BLOCK_SIZE ; 
 scalar_t__ EAP_EKE_MAC_HMAC_SHA1 ; 
 scalar_t__ EAP_EKE_MAC_HMAC_SHA2_256 ; 
 int SHA1_MAC_LEN ; 
 int SHA256_MAC_LEN ; 

__attribute__((used)) static int eap_eke_pnonce_len(u8 mac)
{
	int mac_len;

	if (mac == EAP_EKE_MAC_HMAC_SHA1)
		mac_len = SHA1_MAC_LEN;
	else if (mac == EAP_EKE_MAC_HMAC_SHA2_256)
		mac_len = SHA256_MAC_LEN;
	else
		return -1;

	return AES_BLOCK_SIZE + 16 + mac_len;
}