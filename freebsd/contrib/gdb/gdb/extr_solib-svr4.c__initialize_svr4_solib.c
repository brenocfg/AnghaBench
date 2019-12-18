#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  in_dynsym_resolve_code; int /*<<< orphan*/  open_symbol_file_object; int /*<<< orphan*/  current_sos; int /*<<< orphan*/  special_symbol_handling; int /*<<< orphan*/  solib_create_inferior_hook; int /*<<< orphan*/  clear_solib; int /*<<< orphan*/  free_so; int /*<<< orphan*/  relocate_section_addresses; } ;

/* Variables and functions */
 TYPE_1__* current_target_so_ops ; 
 int /*<<< orphan*/  fetch_link_map_offsets_gdbarch_data ; 
 int /*<<< orphan*/  init_fetch_link_map_offsets ; 
 int /*<<< orphan*/  open_symbol_file_object ; 
 int /*<<< orphan*/  register_gdbarch_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svr4_clear_solib ; 
 int /*<<< orphan*/  svr4_current_sos ; 
 int /*<<< orphan*/  svr4_free_so ; 
 int /*<<< orphan*/  svr4_in_dynsym_resolve_code ; 
 int /*<<< orphan*/  svr4_relocate_section_addresses ; 
 TYPE_1__ svr4_so_ops ; 
 int /*<<< orphan*/  svr4_solib_create_inferior_hook ; 
 int /*<<< orphan*/  svr4_special_symbol_handling ; 

void
_initialize_svr4_solib (void)
{
  fetch_link_map_offsets_gdbarch_data =
    register_gdbarch_data (init_fetch_link_map_offsets);

  svr4_so_ops.relocate_section_addresses = svr4_relocate_section_addresses;
  svr4_so_ops.free_so = svr4_free_so;
  svr4_so_ops.clear_solib = svr4_clear_solib;
  svr4_so_ops.solib_create_inferior_hook = svr4_solib_create_inferior_hook;
  svr4_so_ops.special_symbol_handling = svr4_special_symbol_handling;
  svr4_so_ops.current_sos = svr4_current_sos;
  svr4_so_ops.open_symbol_file_object = open_symbol_file_object;
  svr4_so_ops.in_dynsym_resolve_code = svr4_in_dynsym_resolve_code;

  /* FIXME: Don't do this here.  *_gdbarch_init() should set so_ops. */
  current_target_so_ops = &svr4_so_ops;
}