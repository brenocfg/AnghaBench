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
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  int* fe51 ;

/* Variables and functions */

__attribute__((used)) static void fe51_cswap(fe51 f, fe51 g, unsigned int b)
{
    int i;
    uint64_t mask = 0 - (uint64_t)b;

    for (i = 0; i < 5; i++) {
        int64_t x = f[i] ^ g[i];
        x &= mask;
        f[i] ^= x;
        g[i] ^= x;
    }
}