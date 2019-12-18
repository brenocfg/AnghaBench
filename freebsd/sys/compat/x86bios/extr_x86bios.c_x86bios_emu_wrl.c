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
struct x86emu {int dummy; } ;

/* Variables and functions */
 int htole32 (int) ; 
 int /*<<< orphan*/  le32enc (int*,int) ; 
 int* x86bios_get_pages (int,int) ; 
 int /*<<< orphan*/  x86bios_set_fault (struct x86emu*,int) ; 

__attribute__((used)) static void
x86bios_emu_wrl(struct x86emu *emu, uint32_t addr, uint32_t val)
{
	uint32_t *va;

	va = x86bios_get_pages(addr, sizeof(*va));
	if (va == NULL)
		x86bios_set_fault(emu, addr);

#ifndef __NO_STRICT_ALIGNMENT
	if ((addr & 3) != 0)
		le32enc(va, val);
	else
#endif
	*va = htole32(val);
}