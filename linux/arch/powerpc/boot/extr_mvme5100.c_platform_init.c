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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  _dtb_start ; 
 scalar_t__ _end ; 
 int /*<<< orphan*/  fdt_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_console_init () ; 
 int /*<<< orphan*/  simple_alloc_init (scalar_t__,scalar_t__,int,int) ; 

void platform_init(unsigned long r3, unsigned long r4, unsigned long r5)
{
	u32			heapsize;

	heapsize = 0x8000000 - (u32)_end; /* 128M */
	simple_alloc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_start);
	serial_console_init();
}