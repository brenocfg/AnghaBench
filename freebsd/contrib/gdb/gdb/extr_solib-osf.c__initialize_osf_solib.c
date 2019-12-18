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
 int /*<<< orphan*/  osf_clear_solib ; 
 int /*<<< orphan*/  osf_current_sos ; 
 int /*<<< orphan*/  osf_free_so ; 
 int /*<<< orphan*/  osf_in_dynsym_resolve_code ; 
 int /*<<< orphan*/  osf_open_symbol_file_object ; 
 int /*<<< orphan*/  osf_relocate_section_addresses ; 
 TYPE_1__ osf_so_ops ; 
 int /*<<< orphan*/  osf_solib_create_inferior_hook ; 
 int /*<<< orphan*/  osf_special_symbol_handling ; 

void
_initialize_osf_solib (void)
{
  osf_so_ops.relocate_section_addresses = osf_relocate_section_addresses;
  osf_so_ops.free_so = osf_free_so;
  osf_so_ops.clear_solib = osf_clear_solib;
  osf_so_ops.solib_create_inferior_hook = osf_solib_create_inferior_hook;
  osf_so_ops.special_symbol_handling = osf_special_symbol_handling;
  osf_so_ops.current_sos = osf_current_sos;
  osf_so_ops.open_symbol_file_object = osf_open_symbol_file_object;
  osf_so_ops.in_dynsym_resolve_code = osf_in_dynsym_resolve_code;

  /* FIXME: Don't do this here.  *_gdbarch_init() should set so_ops. */
  current_target_so_ops = &osf_so_ops;
}