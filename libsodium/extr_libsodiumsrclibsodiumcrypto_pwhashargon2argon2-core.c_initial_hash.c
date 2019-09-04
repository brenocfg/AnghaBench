#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  crypto_generichash_blake2b_state ;
typedef  scalar_t__ argon2_type ;
struct TYPE_3__ {int lanes; int outlen; int m_cost; int t_cost; int pwdlen; int flags; int saltlen; int secretlen; int adlen; int /*<<< orphan*/ * ad; int /*<<< orphan*/ * secret; int /*<<< orphan*/ * salt; int /*<<< orphan*/ * pwd; } ;
typedef  TYPE_1__ argon2_context ;

/* Variables and functions */
 int ARGON2_FLAG_CLEAR_PASSWORD ; 
 int ARGON2_FLAG_CLEAR_SECRET ; 
 int /*<<< orphan*/  ARGON2_PREHASH_DIGEST_LENGTH ; 
 int ARGON2_VERSION_NUMBER ; 
 int /*<<< orphan*/  STORE32_LE (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  crypto_generichash_blake2b_final (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_generichash_blake2b_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_generichash_blake2b_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sodium_memzero (int /*<<< orphan*/ *,int) ; 

void
initial_hash(uint8_t *blockhash, argon2_context *context, argon2_type type)
{
    crypto_generichash_blake2b_state BlakeHash;
    uint8_t                          value[4U /* sizeof(uint32_t) */];

    if (NULL == context || NULL == blockhash) {
        return; /* LCOV_EXCL_LINE */
    }

    crypto_generichash_blake2b_init(&BlakeHash, NULL, 0U,
                                    ARGON2_PREHASH_DIGEST_LENGTH);

    STORE32_LE(value, context->lanes);
    crypto_generichash_blake2b_update(&BlakeHash, value, sizeof(value));

    STORE32_LE(value, context->outlen);
    crypto_generichash_blake2b_update(&BlakeHash, value, sizeof(value));

    STORE32_LE(value, context->m_cost);
    crypto_generichash_blake2b_update(&BlakeHash, value, sizeof(value));

    STORE32_LE(value, context->t_cost);
    crypto_generichash_blake2b_update(&BlakeHash, value, sizeof(value));

    STORE32_LE(value, ARGON2_VERSION_NUMBER);
    crypto_generichash_blake2b_update(&BlakeHash, value, sizeof(value));

    STORE32_LE(value, (uint32_t) type);
    crypto_generichash_blake2b_update(&BlakeHash, value, sizeof(value));

    STORE32_LE(value, context->pwdlen);
    crypto_generichash_blake2b_update(&BlakeHash, value, sizeof(value));

    if (context->pwd != NULL) {
        crypto_generichash_blake2b_update(
            &BlakeHash, (const uint8_t *) context->pwd, context->pwdlen);

        /* LCOV_EXCL_START */
        if (context->flags & ARGON2_FLAG_CLEAR_PASSWORD) {
            sodium_memzero(context->pwd, context->pwdlen);
            context->pwdlen = 0;
        }
        /* LCOV_EXCL_STOP */
    }

    STORE32_LE(value, context->saltlen);
    crypto_generichash_blake2b_update(&BlakeHash, value, sizeof(value));

    if (context->salt != NULL) {
        crypto_generichash_blake2b_update(
            &BlakeHash, (const uint8_t *) context->salt, context->saltlen);
    }

    STORE32_LE(value, context->secretlen);
    crypto_generichash_blake2b_update(&BlakeHash, value, sizeof(value));

    /* LCOV_EXCL_START */
    if (context->secret != NULL) {
        crypto_generichash_blake2b_update(
            &BlakeHash, (const uint8_t *) context->secret, context->secretlen);

        if (context->flags & ARGON2_FLAG_CLEAR_SECRET) {
            sodium_memzero(context->secret, context->secretlen);
            context->secretlen = 0;
        }
    }
    /* LCOV_EXCL_STOP */

    STORE32_LE(value, context->adlen);
    crypto_generichash_blake2b_update(&BlakeHash, value, sizeof(value));

    /* LCOV_EXCL_START */
    if (context->ad != NULL) {
        crypto_generichash_blake2b_update(
            &BlakeHash, (const uint8_t *) context->ad, context->adlen);
    }
    /* LCOV_EXCL_STOP */

    crypto_generichash_blake2b_final(&BlakeHash, blockhash,
                                     ARGON2_PREHASH_DIGEST_LENGTH);
}