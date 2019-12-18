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
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  X86BIOS_IVT_SIZE ; 
 int /*<<< orphan*/  X86BIOS_ROM_SIZE ; 
 int /*<<< orphan*/  X86BIOS_SEG_SIZE ; 
 int /*<<< orphan*/  contigfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_unmapbios (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_unmapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * x86bios_ivt ; 
 int /*<<< orphan*/ * x86bios_map ; 
 int /*<<< orphan*/ * x86bios_rom ; 
 int /*<<< orphan*/ * x86bios_seg ; 

__attribute__((used)) static __inline void
x86bios_unmap_mem(void)
{

	if (x86bios_map != NULL) {
		free(x86bios_map, M_DEVBUF);
		x86bios_map = NULL;
	}
	if (x86bios_ivt != NULL) {
#ifdef X86BIOS_NATIVE_ARCH
		pmap_unmapbios((vm_offset_t)x86bios_ivt, X86BIOS_IVT_SIZE);
#else
		free(x86bios_ivt, M_DEVBUF);
		x86bios_ivt = NULL;
#endif
	}
	if (x86bios_rom != NULL)
		pmap_unmapdev((vm_offset_t)x86bios_rom, X86BIOS_ROM_SIZE);
	if (x86bios_seg != NULL) {
		contigfree(x86bios_seg, X86BIOS_SEG_SIZE, M_DEVBUF);
		x86bios_seg = NULL;
	}
}