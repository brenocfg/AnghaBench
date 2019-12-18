#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fixups; } ;

/* Variables and functions */
 scalar_t__ _end ; 
 unsigned long epapr_magic ; 
 unsigned long fdt_addr ; 
 int /*<<< orphan*/  fdt_init (void*) ; 
 unsigned long ima_size ; 
 int /*<<< orphan*/  platform_fixups ; 
 TYPE_1__ platform_ops ; 
 int /*<<< orphan*/  serial_console_init () ; 
 int /*<<< orphan*/  simple_alloc_init (scalar_t__,unsigned long,int,int) ; 

void epapr_platform_init(unsigned long r3, unsigned long r4, unsigned long r5,
			 unsigned long r6, unsigned long r7)
{
	epapr_magic = r6;
	ima_size = r7;
	fdt_addr = r3;

	/* FIXME: we should process reserve entries */

	simple_alloc_init(_end, ima_size - (unsigned long)_end, 32, 64);

	fdt_init((void *)fdt_addr);

	serial_console_init();
	platform_ops.fixups = platform_fixups;
}