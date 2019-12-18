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
 int /*<<< orphan*/  DNSCRYPT_SHARED_SECRET_KEY_LENGTH ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int crypto_box_SECRETKEYBYTES ; 
 int /*<<< orphan*/  hashlittle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint32_t
dnsc_shared_secrets_cache_key(uint8_t* key,
                              uint8_t esversion,
                              uint8_t* pk,
                              uint8_t* sk)
{
    key[0] = esversion;
    memcpy(key + 1, pk, crypto_box_PUBLICKEYBYTES);
    memcpy(key + 1 + crypto_box_PUBLICKEYBYTES, sk, crypto_box_SECRETKEYBYTES);
    return hashlittle(key, DNSCRYPT_SHARED_SECRET_KEY_LENGTH, 0);
}