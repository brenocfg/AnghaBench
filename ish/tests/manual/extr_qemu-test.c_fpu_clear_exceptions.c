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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */

void fpu_clear_exceptions(void)
{
    struct QEMU_PACKED {
        uint16_t fpuc;
        uint16_t dummy1;
        uint16_t fpus;
        uint16_t dummy2;
        uint16_t fptag;
        uint16_t dummy3;
        uint32_t ignored[4];
        long double fpregs[8];
    } float_env32;

    asm volatile ("fnstenv %0\n" : "=m" (float_env32));
    float_env32.fpus &= ~0x7f;
    asm volatile ("fldenv %0\n" : : "m" (float_env32));
}