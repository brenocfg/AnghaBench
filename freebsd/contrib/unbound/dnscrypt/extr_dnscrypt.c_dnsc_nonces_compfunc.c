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
struct nonce_cache_key {int /*<<< orphan*/  client_publickey; int /*<<< orphan*/  magic_query; int /*<<< orphan*/  nonce; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNSCRYPT_MAGIC_HEADER_LEN ; 
 int /*<<< orphan*/  crypto_box_HALF_NONCEBYTES ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 scalar_t__ sodium_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dnsc_nonces_compfunc(void *m1, void *m2)
{
    struct nonce_cache_key *k1 = m1, *k2 = m2;
    return
        sodium_memcmp(
            k1->nonce,
            k2->nonce,
            crypto_box_HALF_NONCEBYTES) != 0 ||
        sodium_memcmp(
            k1->magic_query,
            k2->magic_query,
            DNSCRYPT_MAGIC_HEADER_LEN) != 0 ||
        sodium_memcmp(
            k1->client_publickey, k2->client_publickey,
            crypto_box_PUBLICKEYBYTES) != 0;
}