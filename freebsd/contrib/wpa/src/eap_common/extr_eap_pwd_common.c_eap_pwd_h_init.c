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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_hash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_HASH_ALG_HMAC_SHA256 ; 
 int SHA256_MAC_LEN ; 
 struct crypto_hash* crypto_hash_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

struct crypto_hash * eap_pwd_h_init(void)
{
	u8 allzero[SHA256_MAC_LEN];
	os_memset(allzero, 0, SHA256_MAC_LEN);
	return crypto_hash_init(CRYPTO_HASH_ALG_HMAC_SHA256, allzero,
				SHA256_MAC_LEN);
}