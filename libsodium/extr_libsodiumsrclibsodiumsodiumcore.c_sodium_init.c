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

/* Variables and functions */
 int /*<<< orphan*/  _crypto_generichash_blake2b_pick_best_implementation () ; 
 int /*<<< orphan*/  _crypto_onetimeauth_poly1305_pick_best_implementation () ; 
 int /*<<< orphan*/  _crypto_pwhash_argon2_pick_best_implementation () ; 
 int /*<<< orphan*/  _crypto_scalarmult_curve25519_pick_best_implementation () ; 
 int /*<<< orphan*/  _crypto_stream_chacha20_pick_best_implementation () ; 
 int /*<<< orphan*/  _crypto_stream_salsa20_pick_best_implementation () ; 
 int /*<<< orphan*/  _sodium_alloc_init () ; 
 int /*<<< orphan*/  _sodium_runtime_get_cpu_features () ; 
 int initialized ; 
 int /*<<< orphan*/  randombytes_stir () ; 
 scalar_t__ sodium_crit_enter () ; 
 scalar_t__ sodium_crit_leave () ; 

int
sodium_init(void)
{
    if (sodium_crit_enter() != 0) {
        return -1; /* LCOV_EXCL_LINE */
    }
    if (initialized != 0) {
        if (sodium_crit_leave() != 0) {
            return -1; /* LCOV_EXCL_LINE */
        }
        return 1;
    }
    _sodium_runtime_get_cpu_features();
    randombytes_stir();
    _sodium_alloc_init();
    _crypto_pwhash_argon2_pick_best_implementation();
    _crypto_generichash_blake2b_pick_best_implementation();
    _crypto_onetimeauth_poly1305_pick_best_implementation();
    _crypto_scalarmult_curve25519_pick_best_implementation();
    _crypto_stream_chacha20_pick_best_implementation();
    _crypto_stream_salsa20_pick_best_implementation();
    initialized = 1;
    if (sodium_crit_leave() != 0) {
        return -1; /* LCOV_EXCL_LINE */
    }
    return 0;
}