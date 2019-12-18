#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ui_file {int dummy; } ;
struct TYPE_6__ {scalar_t__ list; } ;
struct TYPE_5__ {scalar_t__ list; } ;
struct partial_symtab {int number_of_dependencies; scalar_t__ n_global_syms; scalar_t__ n_static_syms; scalar_t__ statics_offset; TYPE_3__ static_psymbols; scalar_t__ globals_offset; TYPE_2__ global_psymbols; int /*<<< orphan*/  filename; struct partial_symtab** dependencies; int /*<<< orphan*/  texthigh; int /*<<< orphan*/  textlow; int /*<<< orphan*/  section_offsets; TYPE_1__* objfile; struct partial_symtab* read_symtab; struct partial_symtab* symtab; scalar_t__ readin; int /*<<< orphan*/  name; } ;
struct objfile {int number_of_dependencies; scalar_t__ n_global_syms; scalar_t__ n_static_syms; scalar_t__ statics_offset; TYPE_3__ static_psymbols; scalar_t__ globals_offset; TYPE_2__ global_psymbols; int /*<<< orphan*/  filename; struct objfile** dependencies; int /*<<< orphan*/  texthigh; int /*<<< orphan*/  textlow; int /*<<< orphan*/  section_offsets; TYPE_1__* objfile; struct objfile* read_symtab; struct objfile* symtab; scalar_t__ readin; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int num_sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANOFFSET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fprintf_unfiltered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  gdb_print_host_address (struct partial_symtab*,struct ui_file*) ; 
 int /*<<< orphan*/  print_address_numeric (int /*<<< orphan*/ ,int,struct ui_file*) ; 
 int /*<<< orphan*/  print_partial_symbols (scalar_t__,scalar_t__,char*,struct ui_file*) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
dump_psymtab (struct objfile *objfile, struct partial_symtab *psymtab,
	      struct ui_file *outfile)
{
  int i;

  fprintf_filtered (outfile, "\nPartial symtab for source file %s ",
		    psymtab->filename);
  fprintf_filtered (outfile, "(object ");
  gdb_print_host_address (psymtab, outfile);
  fprintf_filtered (outfile, ")\n\n");
  fprintf_unfiltered (outfile, "  Read from object file %s (",
		      objfile->name);
  gdb_print_host_address (objfile, outfile);
  fprintf_unfiltered (outfile, ")\n");

  if (psymtab->readin)
    {
      fprintf_filtered (outfile,
			"  Full symtab was read (at ");
      gdb_print_host_address (psymtab->symtab, outfile);
      fprintf_filtered (outfile, " by function at ");
      gdb_print_host_address (psymtab->read_symtab, outfile);
      fprintf_filtered (outfile, ")\n");
    }

  fprintf_filtered (outfile, "  Relocate symbols by ");
  for (i = 0; i < psymtab->objfile->num_sections; ++i)
    {
      if (i != 0)
	fprintf_filtered (outfile, ", ");
      wrap_here ("    ");
      print_address_numeric (ANOFFSET (psymtab->section_offsets, i),
			     1,
			     outfile);
    }
  fprintf_filtered (outfile, "\n");

  fprintf_filtered (outfile, "  Symbols cover text addresses ");
  print_address_numeric (psymtab->textlow, 1, outfile);
  fprintf_filtered (outfile, "-");
  print_address_numeric (psymtab->texthigh, 1, outfile);
  fprintf_filtered (outfile, "\n");
  fprintf_filtered (outfile, "  Depends on %d other partial symtabs.\n",
		    psymtab->number_of_dependencies);
  for (i = 0; i < psymtab->number_of_dependencies; i++)
    {
      fprintf_filtered (outfile, "    %d ", i);
      gdb_print_host_address (psymtab->dependencies[i], outfile);
      fprintf_filtered (outfile, " %s\n",
			psymtab->dependencies[i]->filename);
    }
  if (psymtab->n_global_syms > 0)
    {
      print_partial_symbols (objfile->global_psymbols.list
			     + psymtab->globals_offset,
			     psymtab->n_global_syms, "Global", outfile);
    }
  if (psymtab->n_static_syms > 0)
    {
      print_partial_symbols (objfile->static_psymbols.list
			     + psymtab->statics_offset,
			     psymtab->n_static_syms, "Static", outfile);
    }
  fprintf_filtered (outfile, "\n");
}