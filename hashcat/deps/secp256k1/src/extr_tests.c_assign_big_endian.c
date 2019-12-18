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

__attribute__((used)) static void assign_big_endian(unsigned char *ptr, size_t ptrlen, uint32_t val) {
    size_t i;
    for (i = 0; i < ptrlen; i++) {
        int shift = ptrlen - 1 - i;
        if (shift >= 4) {
            ptr[i] = 0;
        } else {
            ptr[i] = (val >> shift) & 0xFF;
        }
    }
}