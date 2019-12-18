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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DNSCRYPT_MAGIC_HEADER_LEN ; 
 int /*<<< orphan*/  crypto_box_HALF_NONCEBYTES ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  hashlittle (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
dnsc_nonce_cache_key_hash(const uint8_t nonce[crypto_box_HALF_NONCEBYTES],
                          const uint8_t magic_query[DNSCRYPT_MAGIC_HEADER_LEN],
                          const uint8_t pk[crypto_box_PUBLICKEYBYTES])
{
    uint32_t h = 0;
    h = hashlittle(nonce, crypto_box_HALF_NONCEBYTES, h);
    h = hashlittle(magic_query, DNSCRYPT_MAGIC_HEADER_LEN, h);
    return hashlittle(pk, crypto_box_PUBLICKEYBYTES, h);
}