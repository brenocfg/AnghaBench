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
 unsigned int MPIDR_HWID_BITMASK ; 

__attribute__((used)) static int read_mpidr(void)
{
	unsigned int id;
	asm volatile ("mrc p15, 0, %0, c0, c0, 5" : "=r" (id));
	return id & MPIDR_HWID_BITMASK;
}