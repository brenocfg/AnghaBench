#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uECC_word_t ;
typedef  TYPE_1__* uECC_Curve ;
struct TYPE_5__ {int num_words; int /*<<< orphan*/  num_bytes; int /*<<< orphan*/  p; int /*<<< orphan*/  (* mod_sqrt ) (int*,TYPE_1__*) ;int /*<<< orphan*/  (* x_side ) (int*,int*,TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int*,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int*,TYPE_1__*) ; 
 int uECC_MAX_WORDS ; 
 int /*<<< orphan*/  uECC_vli_bytesToNative (int*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uECC_vli_nativeToBytes (int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  uECC_vli_sub (int*,int /*<<< orphan*/ ,int*,int) ; 

void uECC_decompress(const uint8_t *compressed, uint8_t *public_key, uECC_Curve curve) {
#if uECC_VLI_NATIVE_LITTLE_ENDIAN
    uECC_word_t *point = (uECC_word_t *)public_key;
#else
    uECC_word_t point[uECC_MAX_WORDS * 2];
#endif
    uECC_word_t *y = point + curve->num_words;
#if uECC_VLI_NATIVE_LITTLE_ENDIAN
    bcopy(public_key, compressed+1, curve->num_bytes);
#else
    uECC_vli_bytesToNative(point, compressed + 1, curve->num_bytes);
#endif
    curve->x_side(y, point, curve);
    curve->mod_sqrt(y, curve);

    if ((y[0] & 0x01) != (compressed[0] & 0x01)) {
        uECC_vli_sub(y, curve->p, y, curve->num_words);
    }

#if uECC_VLI_NATIVE_LITTLE_ENDIAN == 0
    uECC_vli_nativeToBytes(public_key, curve->num_bytes, point);
    uECC_vli_nativeToBytes(public_key + curve->num_bytes, curve->num_bytes, y);
#endif
}