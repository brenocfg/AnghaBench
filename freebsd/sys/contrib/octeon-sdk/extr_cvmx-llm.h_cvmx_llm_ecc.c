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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_DPOP (int,int) ; 

__attribute__((used)) static inline int cvmx_llm_ecc(uint64_t value)
{
    /* FIXME: This needs a re-write */
    static const uint32_t ecc_code_29[7] = {
        0x08962595,
        0x112a4aaa,
        0x024c934f,
        0x04711c73,
        0x0781e07c,
        0x1801ff80,
        0x1ffe0000};
    uint64_t pop0, pop1, pop2, pop3, pop4, pop5, pop6;

    pop0 = ecc_code_29[0];
    pop1 = ecc_code_29[1];
    pop2 = ecc_code_29[2];
    pop0 &= value;
    pop3 = ecc_code_29[3];
    CVMX_DPOP(pop0, pop0);
    pop4 = ecc_code_29[4];
    pop1 &= value;
    CVMX_DPOP(pop1, pop1);
    pop2 &= value;
    pop5 = ecc_code_29[5];
    CVMX_DPOP(pop2, pop2);
    pop6 = ecc_code_29[6];
    pop3 &= value;
    CVMX_DPOP(pop3, pop3);
    pop4 &= value;
    CVMX_DPOP(pop4, pop4);
    pop5 &= value;
    CVMX_DPOP(pop5, pop5);
    pop6 &= value;
    CVMX_DPOP(pop6, pop6);

    return((pop6&1)<<6) | ((pop5&1)<<5) | ((pop4&1)<<4) | ((pop3&1)<<3) | ((pop2&1)<<2) | ((pop1&1)<<1) | (pop0&1);
}