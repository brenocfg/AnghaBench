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

__attribute__((used)) static int
ristretto255_is_canonical(const unsigned char *s)
{
    unsigned char c;
    unsigned char d;
    unsigned int  i;

    c = (s[31] & 0x7f) ^ 0x7f;
    for (i = 30; i > 0; i--) {
        c |= s[i] ^ 0xff;
    }
    c = (((unsigned int) c) - 1U) >> 8;
    d = (0xed - 1U - (unsigned int) s[0]) >> 8;

    return 1 - (((c & d) | s[0]) & 1);
}