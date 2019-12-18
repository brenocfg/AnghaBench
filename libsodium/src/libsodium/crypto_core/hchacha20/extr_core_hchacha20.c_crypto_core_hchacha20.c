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
typedef  int uint32_t ;

/* Variables and functions */
 int LOAD32_LE (unsigned char const*) ; 
 int /*<<< orphan*/  QUARTERROUND (int,int,int,int) ; 
 int /*<<< orphan*/  STORE32_LE (unsigned char*,int) ; 

int
crypto_core_hchacha20(unsigned char *out, const unsigned char *in,
                      const unsigned char *k, const unsigned char *c)
{
    int      i;
    uint32_t x0, x1, x2, x3, x4, x5, x6, x7;
    uint32_t x8, x9, x10, x11, x12, x13, x14, x15;

    if (c == NULL) {
        x0 = 0x61707865;
        x1 = 0x3320646e;
        x2 = 0x79622d32;
        x3 = 0x6b206574;
    } else {
        x0 = LOAD32_LE(c +  0);
        x1 = LOAD32_LE(c +  4);
        x2 = LOAD32_LE(c +  8);
        x3 = LOAD32_LE(c + 12);
    }
    x4  = LOAD32_LE(k +  0);
    x5  = LOAD32_LE(k +  4);
    x6  = LOAD32_LE(k +  8);
    x7  = LOAD32_LE(k + 12);
    x8  = LOAD32_LE(k + 16);
    x9  = LOAD32_LE(k + 20);
    x10 = LOAD32_LE(k + 24);
    x11 = LOAD32_LE(k + 28);
    x12 = LOAD32_LE(in +  0);
    x13 = LOAD32_LE(in +  4);
    x14 = LOAD32_LE(in +  8);
    x15 = LOAD32_LE(in + 12);

    for (i = 0; i < 10; i++) {
        QUARTERROUND(x0, x4,  x8, x12);
        QUARTERROUND(x1, x5,  x9, x13);
        QUARTERROUND(x2, x6, x10, x14);
        QUARTERROUND(x3, x7, x11, x15);
        QUARTERROUND(x0, x5, x10, x15);
        QUARTERROUND(x1, x6, x11, x12);
        QUARTERROUND(x2, x7,  x8, x13);
        QUARTERROUND(x3, x4,  x9, x14);
    }

    STORE32_LE(out +  0, x0);
    STORE32_LE(out +  4, x1);
    STORE32_LE(out +  8, x2);
    STORE32_LE(out + 12, x3);
    STORE32_LE(out + 16, x12);
    STORE32_LE(out + 20, x13);
    STORE32_LE(out + 24, x14);
    STORE32_LE(out + 28, x15);

    return 0;
}