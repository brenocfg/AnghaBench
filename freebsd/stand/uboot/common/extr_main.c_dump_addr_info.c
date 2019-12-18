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
 scalar_t__ __bss_start ; 
 scalar_t__ __sbss_end ; 
 scalar_t__ __sbss_start ; 
 scalar_t__ _edata ; 
 scalar_t__ _end ; 
 scalar_t__ _etext ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ syscall_ptr ; 

__attribute__((used)) static void
dump_addr_info(void)
{
#ifdef DEBUG
	printf("\naddresses info:\n");
	printf(" _etext (sdata) = 0x%08x\n", (uint32_t)_etext);
	printf(" _edata         = 0x%08x\n", (uint32_t)_edata);
	printf(" __sbss_start   = 0x%08x\n", (uint32_t)__sbss_start);
	printf(" __sbss_end     = 0x%08x\n", (uint32_t)__sbss_end);
	printf(" __sbss_start   = 0x%08x\n", (uint32_t)__bss_start);
	printf(" _end           = 0x%08x\n", (uint32_t)_end);
	printf(" syscall entry  = 0x%08x\n", (uint32_t)syscall_ptr);
#endif
}