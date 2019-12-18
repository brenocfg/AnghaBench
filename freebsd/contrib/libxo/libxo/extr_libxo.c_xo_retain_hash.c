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
 int RETAIN_HASH_SIZE ; 

__attribute__((used)) static unsigned
xo_retain_hash (const char *fmt)
{
    volatile uintptr_t iptr = (uintptr_t) (const void *) fmt;

    /* Discard low four bits and high bits; they aren't interesting */
    uint32_t val = (uint32_t) ((iptr >> 4) & (((1 << 24) - 1)));

    val = (val ^ 61) ^ (val >> 16);
    val = val + (val << 3);
    val = val ^ (val >> 4);
    val = val * 0x3a8f05c5;	/* My large prime number */
    val = val ^ (val >> 15);
    val &= RETAIN_HASH_SIZE - 1;

    return val;
}