#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int wordcount_t ;
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int uECC_word_t ;
typedef  TYPE_1__* uECC_Curve ;
typedef  int bitcount_t ;
struct TYPE_6__ {int num_words; int num_n_bits; scalar_t__ num_bytes; int /*<<< orphan*/  n; int /*<<< orphan*/  G; } ;

/* Variables and functions */
 scalar_t__ BITS_TO_BYTES (int) ; 
 int BITS_TO_WORDS (int) ; 
 int /*<<< orphan*/  EccPoint_mult (int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  bits2int (int*,int /*<<< orphan*/  const*,unsigned int,TYPE_1__*) ; 
 int /*<<< orphan*/  g_rng_function ; 
 int regularize_k (int*,int*,int*,TYPE_1__*) ; 
 int uECC_MAX_WORDS ; 
 int /*<<< orphan*/  uECC_generate_random_int (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uECC_vli_bytesToNative (int*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  uECC_vli_clear (int*,int) ; 
 int uECC_vli_cmp (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ uECC_vli_isZero (int*,int) ; 
 int /*<<< orphan*/  uECC_vli_modAdd (int*,int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uECC_vli_modInv (int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uECC_vli_modMult (int*,int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uECC_vli_nativeToBytes (int /*<<< orphan*/  const*,scalar_t__,int*) ; 
 int uECC_vli_numBits (int*,int) ; 
 int /*<<< orphan*/  uECC_vli_set (int*,int*,int) ; 

__attribute__((used)) static int uECC_sign_with_k(const uint8_t *private_key,
                            const uint8_t *message_hash,
                            unsigned hash_size,
                            uECC_word_t *k,
                            uint8_t *signature,
                            uECC_Curve curve) {

    uECC_word_t tmp[uECC_MAX_WORDS];
    uECC_word_t s[uECC_MAX_WORDS];
    uECC_word_t *k2[2] = {tmp, s};
#if uECC_VLI_NATIVE_LITTLE_ENDIAN
    uECC_word_t *p = (uECC_word_t *)signature;
#else
    uECC_word_t p[uECC_MAX_WORDS * 2];
#endif
    uECC_word_t carry;
    wordcount_t num_words = curve->num_words;
    wordcount_t num_n_words = BITS_TO_WORDS(curve->num_n_bits);
    bitcount_t num_n_bits = curve->num_n_bits;

    /* Make sure 0 < k < curve_n */
    if (uECC_vli_isZero(k, num_words) || uECC_vli_cmp(curve->n, k, num_n_words) != 1) {
        return 0;
    }

    carry = regularize_k(k, tmp, s, curve);
    EccPoint_mult(p, curve->G, k2[!carry], 0, num_n_bits + 1, curve);
    if (uECC_vli_isZero(p, num_words)) {
        return 0;
    }

    /* If an RNG function was specified, get a random number
       to prevent side channel analysis of k. */
    if (!g_rng_function) {
        uECC_vli_clear(tmp, num_n_words);
        tmp[0] = 1;
    } else if (!uECC_generate_random_int(tmp, curve->n, num_n_words)) {
        return 0;
    }

    /* Prevent side channel analysis of uECC_vli_modInv() to determine
       bits of k / the private key by premultiplying by a random number */
    uECC_vli_modMult(k, k, tmp, curve->n, num_n_words); /* k' = rand * k */
    uECC_vli_modInv(k, k, curve->n, num_n_words);       /* k = 1 / k' */
    uECC_vli_modMult(k, k, tmp, curve->n, num_n_words); /* k = 1 / k */

#if uECC_VLI_NATIVE_LITTLE_ENDIAN == 0
    uECC_vli_nativeToBytes(signature, curve->num_bytes, p); /* store r */
#endif

#if uECC_VLI_NATIVE_LITTLE_ENDIAN
    bcopy((uint8_t *) tmp, private_key, BITS_TO_BYTES(curve->num_n_bits));
#else
    uECC_vli_bytesToNative(tmp, private_key, BITS_TO_BYTES(curve->num_n_bits)); /* tmp = d */
#endif

    s[num_n_words - 1] = 0;
    uECC_vli_set(s, p, num_words);
    uECC_vli_modMult(s, tmp, s, curve->n, num_n_words); /* s = r*d */

    bits2int(tmp, message_hash, hash_size, curve);
    uECC_vli_modAdd(s, tmp, s, curve->n, num_n_words); /* s = e + r*d */
    uECC_vli_modMult(s, s, k, curve->n, num_n_words);  /* s = (e + r*d) / k */
    if (uECC_vli_numBits(s, num_n_words) > (bitcount_t)curve->num_bytes * 8) {
        return 0;
    }
#if uECC_VLI_NATIVE_LITTLE_ENDIAN
    bcopy((uint8_t *) signature + curve->num_bytes, (uint8_t *) s, curve->num_bytes);
#else
    uECC_vli_nativeToBytes(signature + curve->num_bytes, curve->num_bytes, s);
#endif    
    return 1;
}