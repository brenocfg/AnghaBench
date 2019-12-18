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
typedef  int /*<<< orphan*/  secp256k1_ge_storage ;
struct TYPE_4__ {int /*<<< orphan*/ ** pre_g_128; int /*<<< orphan*/ ** pre_g; } ;
typedef  TYPE_1__ secp256k1_ecmult_context ;

/* Variables and functions */

__attribute__((used)) static void secp256k1_ecmult_context_finalize_memcpy(secp256k1_ecmult_context *dst, const secp256k1_ecmult_context *src) {
    if (src->pre_g != NULL) {
        /* We cast to void* first to suppress a -Wcast-align warning. */
        dst->pre_g = (secp256k1_ge_storage (*)[])(void*)((unsigned char*)dst + ((unsigned char*)(src->pre_g) - (unsigned char*)src));
    }
#ifdef USE_ENDOMORPHISM
    if (src->pre_g_128 != NULL) {
        dst->pre_g_128 = (secp256k1_ge_storage (*)[])(void*)((unsigned char*)dst + ((unsigned char*)(src->pre_g_128) - (unsigned char*)src));
    }
#endif
}