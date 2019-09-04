#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uECC_word_t ;
typedef  TYPE_1__* uECC_Curve ;
struct TYPE_4__ {int /*<<< orphan*/  num_n_bits; int /*<<< orphan*/  n; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_WORDS (int /*<<< orphan*/ ) ; 
 int uECC_MAX_WORDS ; 
 scalar_t__ uECC_RNG_MAX_TRIES ; 
 int /*<<< orphan*/  uECC_generate_random_int (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uECC_sign_with_k (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int,scalar_t__*,int /*<<< orphan*/ *,TYPE_1__*) ; 

int uECC_sign(const uint8_t *private_key,
              const uint8_t *message_hash,
              unsigned hash_size,
              uint8_t *signature,
              uECC_Curve curve) {
    uECC_word_t k[uECC_MAX_WORDS];
    uECC_word_t tries;

    for (tries = 0; tries < uECC_RNG_MAX_TRIES; ++tries) {
        if (!uECC_generate_random_int(k, curve->n, BITS_TO_WORDS(curve->num_n_bits))) {
            return 0;
        }

        if (uECC_sign_with_k(private_key, message_hash, hash_size, k, signature, curve)) {
            return 1;
        }
    }
    return 0;
}