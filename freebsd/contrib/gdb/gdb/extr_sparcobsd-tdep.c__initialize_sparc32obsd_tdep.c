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
 int /*<<< orphan*/  GDB_OSABI_OPENBSD_ELF ; 
 int /*<<< orphan*/  bfd_arch_sparc ; 
 int /*<<< orphan*/  gdbarch_register_osabi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparc32obsd_init_abi ; 

void
_initialize_sparc32obsd_tdep (void)
{
  gdbarch_register_osabi (bfd_arch_sparc, 0, GDB_OSABI_OPENBSD_ELF,
			  sparc32obsd_init_abi);
}