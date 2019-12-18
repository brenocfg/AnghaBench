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
 unsigned long arch_rnd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmap32_rnd_bits ; 
 int /*<<< orphan*/  mmap64_rnd_bits ; 
 scalar_t__ mmap_is_ia32 () ; 

unsigned long arch_mmap_rnd(void)
{
	return arch_rnd(mmap_is_ia32() ? mmap32_rnd_bits : mmap64_rnd_bits);
}