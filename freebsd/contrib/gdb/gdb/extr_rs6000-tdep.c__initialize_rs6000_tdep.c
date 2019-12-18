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
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_arch_powerpc ; 
 int /*<<< orphan*/  bfd_arch_rs6000 ; 
 int /*<<< orphan*/  class_info ; 
 int /*<<< orphan*/  gdbarch_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info_powerpc_cmdlist ; 
 int /*<<< orphan*/  infolist ; 
 int /*<<< orphan*/  rs6000_dump_tdep ; 
 int /*<<< orphan*/  rs6000_gdbarch_init ; 
 int /*<<< orphan*/  rs6000_info_powerpc_command ; 

void
_initialize_rs6000_tdep (void)
{
  gdbarch_register (bfd_arch_rs6000, rs6000_gdbarch_init, rs6000_dump_tdep);
  gdbarch_register (bfd_arch_powerpc, rs6000_gdbarch_init, rs6000_dump_tdep);

  /* Add root prefix command for "info powerpc" commands */
  add_prefix_cmd ("powerpc", class_info, rs6000_info_powerpc_command,
		  "Various POWERPC info specific commands.",
		  &info_powerpc_cmdlist, "info powerpc ", 0, &infolist);
}