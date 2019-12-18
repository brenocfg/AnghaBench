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
 int /*<<< orphan*/  atomic_clear_acq_long (unsigned long volatile*,int) ; 

void
bxe_clear_bit(int                    nr,
              volatile unsigned long *addr)
{
    atomic_clear_acq_long(addr, (1 << nr));
}