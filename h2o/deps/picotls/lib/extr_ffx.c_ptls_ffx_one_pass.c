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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  ptls_cipher_encrypt (int /*<<< orphan*/ *,int*,int const*,int) ; 
 int /*<<< orphan*/  ptls_cipher_init (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void ptls_ffx_one_pass(ptls_cipher_context_t *enc_ctx, uint8_t *source, size_t source_size, uint8_t *target,
                              size_t target_size, uint8_t mask_last_byte, uint8_t *confusion, uint8_t *iv, uint8_t *tweaks,
                              uint8_t round, uint8_t nb_rounds)
{
    static const uint8_t zeros[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    memcpy(iv, tweaks, 16);
    iv[round & 15] ^= nb_rounds;
    for (size_t i = 0; i < source_size; i++) {
        iv[i] ^= source[i];
    }
    ptls_cipher_init(enc_ctx, iv);
    ptls_cipher_encrypt(enc_ctx, confusion, zeros, 16);
    for (size_t j = 0; j < target_size - 1; j++) {
        target[j] ^= confusion[j];
    }
    target[target_size - 1] ^= (confusion[target_size - 1] & mask_last_byte);
}