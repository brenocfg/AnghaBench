#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symloc {scalar_t__ numsyms; } ;
struct partial_symtab {TYPE_1__* objfile; int /*<<< orphan*/  filename; scalar_t__ number_of_dependencies; scalar_t__ read_symtab_private; scalar_t__ readin; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/ * obfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ info_verbose ; 
 int /*<<< orphan*/  next_symbol_text_func ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  scan_file_globals (TYPE_1__*) ; 
 int /*<<< orphan*/  xcoff_next_symbol_text ; 
 int /*<<< orphan*/  xcoff_psymtab_to_symtab_1 (struct partial_symtab*) ; 

__attribute__((used)) static void
xcoff_psymtab_to_symtab (struct partial_symtab *pst)
{
  bfd *sym_bfd;

  if (!pst)
    return;

  if (pst->readin)
    {
      fprintf_unfiltered
	(gdb_stderr, "Psymtab for %s already read in.  Shouldn't happen.\n",
	 pst->filename);
      return;
    }

  if (((struct symloc *) pst->read_symtab_private)->numsyms != 0
      || pst->number_of_dependencies)
    {
      /* Print the message now, before reading the string table,
         to avoid disconcerting pauses.  */
      if (info_verbose)
	{
	  printf_filtered ("Reading in symbols for %s...", pst->filename);
	  gdb_flush (gdb_stdout);
	}

      sym_bfd = pst->objfile->obfd;

      next_symbol_text_func = xcoff_next_symbol_text;

      xcoff_psymtab_to_symtab_1 (pst);

      /* Match with global symbols.  This only needs to be done once,
         after all of the symtabs and dependencies have been read in.   */
      scan_file_globals (pst->objfile);

      /* Finish up the debug error message.  */
      if (info_verbose)
	printf_filtered ("done.\n");
    }
}