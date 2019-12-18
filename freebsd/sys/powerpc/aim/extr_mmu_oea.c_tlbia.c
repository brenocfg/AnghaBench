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
typedef  int vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  powerpc_sync () ; 

__attribute__((used)) static void
tlbia(void)
{
	vm_offset_t va;

	for (va = 0; va < 0x00040000; va += 0x00001000) {
		__asm __volatile("tlbie %0" :: "r"(va));
		powerpc_sync();
	}
	__asm __volatile("tlbsync");
	powerpc_sync();
}