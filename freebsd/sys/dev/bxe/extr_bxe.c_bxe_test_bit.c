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
 int atomic_load_acq_long (unsigned long volatile*) ; 

int
bxe_test_bit(int                    nr,
             volatile unsigned long *addr)
{
    return ((atomic_load_acq_long(addr) & (1 << nr)) != 0);
}