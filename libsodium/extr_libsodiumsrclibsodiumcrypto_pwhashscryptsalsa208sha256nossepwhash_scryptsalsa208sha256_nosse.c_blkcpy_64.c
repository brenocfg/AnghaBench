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
struct TYPE_4__ {int /*<<< orphan*/ * d; } ;
typedef  TYPE_1__ escrypt_block_t ;

/* Variables and functions */

__attribute__((used)) static inline void
blkcpy_64(escrypt_block_t *dest, const escrypt_block_t *src)
{
    int i;

#if (ARCH_BITS == 32)
    for (i = 0; i < 16; ++i) {
        dest->w[i] = src->w[i];
    }
#else
    for (i = 0; i < 8; ++i) {
        dest->d[i] = src->d[i];
    }
#endif
}