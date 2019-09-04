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
typedef  int uint_fast16_t ;

/* Variables and functions */

void
sodium_increment(unsigned char *n, const size_t nlen)
{
    size_t        i = 0U;
    uint_fast16_t c = 1U;

#ifdef HAVE_AMD64_ASM
    uint64_t t64, t64_2;
    uint32_t t32;

    if (nlen == 12U) {
        __asm__ __volatile__(
            "xorq %[t64], %[t64] \n"
            "xorl %[t32], %[t32] \n"
            "stc \n"
            "adcq %[t64], (%[out]) \n"
            "adcl %[t32], 8(%[out]) \n"
            : [t64] "=&r"(t64), [t32] "=&r"(t32)
            : [out] "D"(n)
            : "memory", "flags", "cc");
        return;
    } else if (nlen == 24U) {
        __asm__ __volatile__(
            "movq $1, %[t64] \n"
            "xorq %[t64_2], %[t64_2] \n"
            "addq %[t64], (%[out]) \n"
            "adcq %[t64_2], 8(%[out]) \n"
            "adcq %[t64_2], 16(%[out]) \n"
            : [t64] "=&r"(t64), [t64_2] "=&r"(t64_2)
            : [out] "D"(n)
            : "memory", "flags", "cc");
        return;
    } else if (nlen == 8U) {
        __asm__ __volatile__("incq (%[out]) \n"
                             :
                             : [out] "D"(n)
                             : "memory", "flags", "cc");
        return;
    }
#endif
    for (; i < nlen; i++) {
        c += (uint_fast16_t) n[i];
        n[i] = (unsigned char) c;
        c >>= 8;
    }
}