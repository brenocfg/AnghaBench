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
struct TYPE_3__ {int* r; int* pad; scalar_t__ final; scalar_t__ leftover; scalar_t__* h; } ;
typedef  TYPE_1__ poly1305_state_internal_t ;

/* Variables and functions */
 int LOAD32_LE (unsigned char const*) ; 

__attribute__((used)) static void
poly1305_init(poly1305_state_internal_t *st, const unsigned char key[32])
{
    /* r &= 0xffffffc0ffffffc0ffffffc0fffffff - wiped after finalization */
    st->r[0] = (LOAD32_LE(&key[0])) & 0x3ffffff;
    st->r[1] = (LOAD32_LE(&key[3]) >> 2) & 0x3ffff03;
    st->r[2] = (LOAD32_LE(&key[6]) >> 4) & 0x3ffc0ff;
    st->r[3] = (LOAD32_LE(&key[9]) >> 6) & 0x3f03fff;
    st->r[4] = (LOAD32_LE(&key[12]) >> 8) & 0x00fffff;

    /* h = 0 */
    st->h[0] = 0;
    st->h[1] = 0;
    st->h[2] = 0;
    st->h[3] = 0;
    st->h[4] = 0;

    /* save pad for later */
    st->pad[0] = LOAD32_LE(&key[16]);
    st->pad[1] = LOAD32_LE(&key[20]);
    st->pad[2] = LOAD32_LE(&key[24]);
    st->pad[3] = LOAD32_LE(&key[28]);

    st->leftover = 0;
    st->final    = 0;
}