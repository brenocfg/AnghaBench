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
typedef  int uint64_t ;

/* Variables and functions */
 size_t GUEST_CODE_SEL ; 
 size_t GUEST_DATA_SEL ; 
 size_t GUEST_NULL_SEL ; 

void     
vm_setup_freebsd_gdt(uint64_t *gdtr)
{       
	gdtr[GUEST_NULL_SEL] = 0;
	gdtr[GUEST_CODE_SEL] = 0x0020980000000000;
	gdtr[GUEST_DATA_SEL] = 0x0000900000000000;
}