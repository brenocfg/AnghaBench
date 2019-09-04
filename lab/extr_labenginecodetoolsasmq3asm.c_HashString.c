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

__attribute__((used)) static unsigned int HashString (const char *key)
{
    static unsigned long randbox[] = {
    0x49848f1bU, 0xe6255dbaU, 0x36da5bdcU, 0x47bf94e9U,
    0x8cbcce22U, 0x559fc06aU, 0xd268f536U, 0xe10af79aU,
    0xc1af4d69U, 0x1d2917b5U, 0xec4c304dU, 0x9ee5016cU,
    0x69232f74U, 0xfead7bb3U, 0xe9089ab6U, 0xf012f6aeU,
    };

    const char *str = key;
    unsigned int acc = 0;

    while (*str) {
    acc ^= randbox[(*str + acc) & 0xf];
    acc = (acc << 1) | (acc >> 31);
    acc &= 0xffffffffU;
    acc ^= randbox[((*str++ >> 4) + acc) & 0xf];
    acc = (acc << 2) | (acc >> 30);
    acc &= 0xffffffffU;
    }
    return acc;
}