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
typedef  int /*<<< orphan*/  crypto_generichash_blake2b_state ;
typedef  int /*<<< orphan*/  blake2b_state ;

/* Variables and functions */
 size_t const BLAKE2B_KEYBYTES ; 
 size_t const BLAKE2B_OUTBYTES ; 
 size_t const UINT8_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ blake2b_init_key_salt_personal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ,unsigned char const*,unsigned char const*) ; 
 scalar_t__ blake2b_init_salt_personal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,unsigned char const*) ; 

int
crypto_generichash_blake2b_init_salt_personal(
    crypto_generichash_blake2b_state *state, const unsigned char *key,
    const size_t keylen, const size_t outlen, const unsigned char *salt,
    const unsigned char *personal)
{
    if (outlen <= 0U || outlen > BLAKE2B_OUTBYTES ||
        keylen > BLAKE2B_KEYBYTES) {
        return -1;
    }
    assert(outlen <= UINT8_MAX);
    assert(keylen <= UINT8_MAX);
    if (key == NULL || keylen <= 0U) {
        if (blake2b_init_salt_personal((blake2b_state *) (void *) state,
                                       (uint8_t) outlen, salt, personal) != 0) {
            return -1; /* LCOV_EXCL_LINE */
        }
    } else if (blake2b_init_key_salt_personal((blake2b_state *) (void *) state,
                                              (uint8_t) outlen, key,
                                              (uint8_t) keylen, salt,
                                              personal) != 0) {
        return -1; /* LCOV_EXCL_LINE */
    }
    return 0;
}