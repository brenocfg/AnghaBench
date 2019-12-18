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
struct cmd_list_element {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  find_and_open_solib; int /*<<< orphan*/  in_dynsym_resolve_code; int /*<<< orphan*/  open_symbol_file_object; int /*<<< orphan*/  current_sos; int /*<<< orphan*/  special_symbol_handling; int /*<<< orphan*/  solib_create_inferior_hook; int /*<<< orphan*/  clear_solib; int /*<<< orphan*/  free_so; int /*<<< orphan*/  relocate_section_addresses; } ;

/* Variables and functions */
 struct cmd_list_element* add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  class_files ; 
 TYPE_1__* current_target_so_ops ; 
 int /*<<< orphan*/  filename_completer ; 
 int /*<<< orphan*/  kgdb_add_kld_cmd ; 
 int /*<<< orphan*/  kld_clear_solib ; 
 int /*<<< orphan*/  kld_current_sos ; 
 int /*<<< orphan*/  kld_find_and_open_solib ; 
 int /*<<< orphan*/  kld_free_so ; 
 int /*<<< orphan*/  kld_in_dynsym_resolve_code ; 
 int /*<<< orphan*/  kld_open_symbol_file_object ; 
 int /*<<< orphan*/  kld_relocate_section_addresses ; 
 TYPE_1__ kld_so_ops ; 
 int /*<<< orphan*/  kld_solib_create_inferior_hook ; 
 int /*<<< orphan*/  kld_special_symbol_handling ; 
 int /*<<< orphan*/  set_cmd_completer (struct cmd_list_element*,int /*<<< orphan*/ ) ; 

void
initialize_kld_target(void)
{
	struct cmd_list_element *c;

	kld_so_ops.relocate_section_addresses = kld_relocate_section_addresses;
	kld_so_ops.free_so = kld_free_so;
	kld_so_ops.clear_solib = kld_clear_solib;
	kld_so_ops.solib_create_inferior_hook = kld_solib_create_inferior_hook;
	kld_so_ops.special_symbol_handling = kld_special_symbol_handling;
	kld_so_ops.current_sos = kld_current_sos;
	kld_so_ops.open_symbol_file_object = kld_open_symbol_file_object;
	kld_so_ops.in_dynsym_resolve_code = kld_in_dynsym_resolve_code;
	kld_so_ops.find_and_open_solib = kld_find_and_open_solib;

	current_target_so_ops = &kld_so_ops;

	c = add_com("add-kld", class_files, kgdb_add_kld_cmd,
	   "Usage: add-kld FILE\n\
Load the symbols from the kernel loadable module FILE.");
	set_cmd_completer(c, filename_completer);
}