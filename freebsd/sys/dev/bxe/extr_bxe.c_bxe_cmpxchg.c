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
 scalar_t__ atomic_cmpset_acq_int (int volatile*,int,int) ; 

int
bxe_cmpxchg(volatile int *addr,
            int          old,
            int          new)
{
    int x;
    do {
        x = *addr;
    } while (atomic_cmpset_acq_int(addr, old, new) == 0);
    return (x);
}