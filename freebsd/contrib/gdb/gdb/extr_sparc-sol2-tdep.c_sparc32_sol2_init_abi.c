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
struct gdbarch_tdep {int plt_entry_size; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_solib_trampoline_target ; 
 int /*<<< orphan*/  frame_unwind_append_sniffer (struct gdbarch*,int /*<<< orphan*/ ) ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  in_plt_section ; 
 int /*<<< orphan*/  set_gdbarch_in_solib_call_trampoline (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_pc_in_sigtramp (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_skip_trampoline_code (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_software_single_step (struct gdbarch*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sparc32_sol2_sigtramp_frame_sniffer ; 
 int /*<<< orphan*/  sparc_sol2_pc_in_sigtramp ; 

void
sparc32_sol2_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* Solaris has SVR4-style shared libraries...  */
  set_gdbarch_in_solib_call_trampoline (gdbarch, in_plt_section);
  set_gdbarch_skip_trampoline_code (gdbarch, find_solib_trampoline_target);

  /* ...which means that we need some special handling when doing
     prologue analysis.  */
  tdep->plt_entry_size = 12;

  /* Solaris has kernel-assisted single-stepping support.  */
  set_gdbarch_software_single_step (gdbarch, NULL);

  set_gdbarch_pc_in_sigtramp (gdbarch, sparc_sol2_pc_in_sigtramp);
  frame_unwind_append_sniffer (gdbarch, sparc32_sol2_sigtramp_frame_sniffer);
}