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
typedef  int /*<<< orphan*/  crypto_hash_sha256_state ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_hash_sha256_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  crypto_hash_sha256_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_hash_sha256_update (int /*<<< orphan*/ *,unsigned char const*,unsigned long long) ; 

int
crypto_hash_sha256(unsigned char *out, const unsigned char *in,
                   unsigned long long inlen)
{
    crypto_hash_sha256_state state;

    crypto_hash_sha256_init(&state);
    crypto_hash_sha256_update(&state, in, inlen);
    crypto_hash_sha256_final(&state, out);

    return 0;
}