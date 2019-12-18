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
 scalar_t__ atomic_cmpset_acq_long (unsigned long volatile*,unsigned long,unsigned long) ; 

int
bxe_test_and_set_bit(int                    nr,
                       volatile unsigned long *addr)
{
    unsigned long x;
    nr = (1 << nr);
    do {
        x = *addr;
    } while (atomic_cmpset_acq_long(addr, x, x | nr) == 0);
    // if (x & nr) bit_was_set; else bit_was_not_set;
    return (x & nr);
}