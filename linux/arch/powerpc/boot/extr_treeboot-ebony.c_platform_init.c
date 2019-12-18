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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ OPENBIOS_MAC_BASE ; 
 scalar_t__ OPENBIOS_MAC_OFFSET ; 
 scalar_t__ _end ; 
 int /*<<< orphan*/  ebony_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_alloc_init (scalar_t__,unsigned long,int,int) ; 

void platform_init(void)
{
	unsigned long end_of_ram = 0x8000000;
	unsigned long avail_ram = end_of_ram - (unsigned long)_end;

	simple_alloc_init(_end, avail_ram, 32, 64);
	ebony_init((u8 *)OPENBIOS_MAC_BASE,
		   (u8 *)(OPENBIOS_MAC_BASE + OPENBIOS_MAC_OFFSET));
}