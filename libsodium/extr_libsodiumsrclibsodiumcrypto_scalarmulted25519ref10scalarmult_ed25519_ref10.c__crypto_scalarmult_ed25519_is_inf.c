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
_crypto_scalarmult_ed25519_is_inf(const unsigned char s[32])
{
    unsigned char c;
    unsigned int  i;

    c = s[0] ^ 0x01;
    for (i = 1; i < 31; i++) {
        c |= s[i];
    }
    c |= s[31] & 0x7f;

    return ((((unsigned int) c) - 1U) >> 8) & 1;
}