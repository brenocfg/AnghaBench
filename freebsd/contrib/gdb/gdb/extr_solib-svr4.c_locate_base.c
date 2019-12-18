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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 scalar_t__ debug_base ; 
 scalar_t__ elf_locate_base () ; 
 int /*<<< orphan*/ * exec_bfd ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  look_for_base ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  proc_iterate_over_mappings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svr4_have_link_map_offsets () ; 
 scalar_t__ target_has_execution ; 

__attribute__((used)) static CORE_ADDR
locate_base (void)
{
  /* Check to see if we have a currently valid address, and if so, avoid
     doing all this work again and just return the cached address.  If
     we have no cached address, try to locate it in the dynamic info
     section for ELF executables.  There's no point in doing any of this
     though if we don't have some link map offsets to work with.  */

  if (debug_base == 0 && svr4_have_link_map_offsets ())
    {
      if (exec_bfd != NULL
	  && bfd_get_flavour (exec_bfd) == bfd_target_elf_flavour)
	debug_base = elf_locate_base ();
#ifdef HANDLE_SVR4_EXEC_EMULATORS
      /* Try it the hard way for emulated executables.  */
      else if (!ptid_equal (inferior_ptid, null_ptid) && target_has_execution)
	proc_iterate_over_mappings (look_for_base);
#endif
    }
  return (debug_base);
}