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
 int /*<<< orphan*/  GDB_OSABI_FREEBSD_ELF ; 
 int /*<<< orphan*/  arm_freebsd_elf_init_abi ; 
 int /*<<< orphan*/  bfd_arch_arm ; 
 int /*<<< orphan*/  gdbarch_register_osabi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
_initialize_armfbsd_tdep (void)
{
  gdbarch_register_osabi (bfd_arch_arm, 0, GDB_OSABI_FREEBSD_ELF,
                          arm_freebsd_elf_init_abi);
}