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
struct objfile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  have_partial_symbols () ; 
 void* kernel_file_addr ; 
 void* kgdb_parse (char*) ; 
 int /*<<< orphan*/  kgdb_parse_quiet (char*) ; 
 void* linker_files_addr ; 
 void* module_path_addr ; 
 void* off_address ; 
 void* off_filename ; 
 void* off_next ; 
 int /*<<< orphan*/  off_pathname ; 

void
kld_new_objfile (struct objfile *objfile)
{

	if (!have_partial_symbols())
		return;

	/*
	 * Compute offsets of relevant members in struct linker_file
	 * and the addresses of global variables.  Don't warn about
	 * kernels that don't have 'pathname' in the linker_file
	 * struct since 6.x kernels don't have it.
	 */
	off_address = kgdb_parse("&((struct linker_file *)0)->address");
	off_filename = kgdb_parse("&((struct linker_file *)0)->filename");
	off_pathname = kgdb_parse_quiet("&((struct linker_file *)0)->pathname");
	off_next = kgdb_parse("&((struct linker_file *)0)->link.tqe_next");
	module_path_addr = kgdb_parse("linker_path");
	linker_files_addr = kgdb_parse("&linker_files.tqh_first");
	kernel_file_addr = kgdb_parse("&linker_kernel_file");
}