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
 int /*<<< orphan*/  open_symbol_file_object ; 
 int /*<<< orphan*/  sunos_clear_solib ; 
 int /*<<< orphan*/  sunos_current_sos ; 
 int /*<<< orphan*/  sunos_free_so ; 
 int /*<<< orphan*/  sunos_in_dynsym_resolve_code ; 
 int /*<<< orphan*/  sunos_relocate_section_addresses ; 
 TYPE_1__ sunos_so_ops ; 
 int /*<<< orphan*/  sunos_solib_create_inferior_hook ; 
 int /*<<< orphan*/  sunos_special_symbol_handling ; 

void
_initialize_sunos_solib (void)
{
  sunos_so_ops.relocate_section_addresses = sunos_relocate_section_addresses;
  sunos_so_ops.free_so = sunos_free_so;
  sunos_so_ops.clear_solib = sunos_clear_solib;
  sunos_so_ops.solib_create_inferior_hook = sunos_solib_create_inferior_hook;
  sunos_so_ops.special_symbol_handling = sunos_special_symbol_handling;
  sunos_so_ops.current_sos = sunos_current_sos;
  sunos_so_ops.open_symbol_file_object = open_symbol_file_object;
  sunos_so_ops.in_dynsym_resolve_code = sunos_in_dynsym_resolve_code;

  /* FIXME: Don't do this here.  *_gdbarch_init() should set so_ops. */
  current_target_so_ops = &sunos_so_ops;
}