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
struct gdbarch_tdep {int /*<<< orphan*/  npc_regnum; int /*<<< orphan*/  pc_regnum; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_ENTRY_POINT ; 
 int /*<<< orphan*/  SPARC64_NPC_REGNUM ; 
 int /*<<< orphan*/  SPARC64_NUM_PSEUDO_REGS ; 
 int /*<<< orphan*/  SPARC64_NUM_REGS ; 
 int /*<<< orphan*/  SPARC64_PC_REGNUM ; 
 int /*<<< orphan*/  default_stabs_argument_has_addr ; 
 int /*<<< orphan*/  frame_base_set_default (struct gdbarch*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_unwind_append_sniffer (struct gdbarch*,int /*<<< orphan*/ ) ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  set_gdbarch_call_dummy_location (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_long_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_long_long_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_num_pseudo_regs (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_num_regs (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_pc_regnum (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_pseudo_register_read (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_pseudo_register_write (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_ptr_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_push_dummy_call (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_push_dummy_code (struct gdbarch*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_gdbarch_register_name (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_register_type (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_return_value (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_skip_prologue (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_stabs_argument_has_addr (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparc64_frame_base ; 
 int /*<<< orphan*/  sparc64_frame_sniffer ; 
 int /*<<< orphan*/  sparc64_pseudo_register_read ; 
 int /*<<< orphan*/  sparc64_pseudo_register_write ; 
 int /*<<< orphan*/  sparc64_push_dummy_call ; 
 int /*<<< orphan*/  sparc64_register_name ; 
 int /*<<< orphan*/  sparc64_register_type ; 
 int /*<<< orphan*/  sparc64_return_value ; 
 int /*<<< orphan*/  sparc64_skip_prologue ; 

void
sparc64_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  tdep->pc_regnum = SPARC64_PC_REGNUM;
  tdep->npc_regnum = SPARC64_NPC_REGNUM;

  /* This is what all the fuss is about.  */
  set_gdbarch_long_bit (gdbarch, 64);
  set_gdbarch_long_long_bit (gdbarch, 64);
  set_gdbarch_ptr_bit (gdbarch, 64);

  set_gdbarch_num_regs (gdbarch, SPARC64_NUM_REGS);
  set_gdbarch_register_name (gdbarch, sparc64_register_name);
  set_gdbarch_register_type (gdbarch, sparc64_register_type);
  set_gdbarch_num_pseudo_regs (gdbarch, SPARC64_NUM_PSEUDO_REGS);
  set_gdbarch_pseudo_register_read (gdbarch, sparc64_pseudo_register_read);
  set_gdbarch_pseudo_register_write (gdbarch, sparc64_pseudo_register_write);

  /* Register numbers of various important registers.  */
  set_gdbarch_pc_regnum (gdbarch, SPARC64_PC_REGNUM); /* %pc */

  /* Call dummy code.  */
  set_gdbarch_call_dummy_location (gdbarch, AT_ENTRY_POINT);
  set_gdbarch_push_dummy_code (gdbarch, NULL);
  set_gdbarch_push_dummy_call (gdbarch, sparc64_push_dummy_call);

  set_gdbarch_return_value (gdbarch, sparc64_return_value);
  set_gdbarch_stabs_argument_has_addr
    (gdbarch, default_stabs_argument_has_addr);

  set_gdbarch_skip_prologue (gdbarch, sparc64_skip_prologue);

  frame_unwind_append_sniffer (gdbarch, sparc64_frame_sniffer);
  frame_base_set_default (gdbarch, &sparc64_frame_base);
}