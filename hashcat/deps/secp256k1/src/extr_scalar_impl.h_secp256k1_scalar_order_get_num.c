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
typedef  int /*<<< orphan*/  secp256k1_num ;

/* Variables and functions */
#define  EXHAUSTIVE_TEST_ORDER 128 
 int /*<<< orphan*/  secp256k1_num_set_bin (int /*<<< orphan*/ *,unsigned char const*,int) ; 

__attribute__((used)) static void secp256k1_scalar_order_get_num(secp256k1_num *r) {
#if defined(EXHAUSTIVE_TEST_ORDER)
    static const unsigned char order[32] = {
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,EXHAUSTIVE_TEST_ORDER
    };
#else
    static const unsigned char order[32] = {
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
        0xBA,0xAE,0xDC,0xE6,0xAF,0x48,0xA0,0x3B,
        0xBF,0xD2,0x5E,0x8C,0xD0,0x36,0x41,0x41
    };
#endif
    secp256k1_num_set_bin(r, order, 32);
}