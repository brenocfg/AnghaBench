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
struct symloc {scalar_t__ numsyms; } ;
struct partial_symtab {int readin; int number_of_dependencies; scalar_t__ read_symtab_private; struct partial_symtab** dependencies; int /*<<< orphan*/  filename; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buildsym_init () ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ info_verbose ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_xcoff_symtab (struct partial_symtab*) ; 
 int /*<<< orphan*/  really_free_pendings ; 
 int /*<<< orphan*/  stabsread_init () ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
xcoff_psymtab_to_symtab_1 (struct partial_symtab *pst)
{
  struct cleanup *old_chain;
  int i;

  if (!pst)
    return;

  if (pst->readin)
    {
      fprintf_unfiltered
	(gdb_stderr, "Psymtab for %s already read in.  Shouldn't happen.\n",
	 pst->filename);
      return;
    }

  /* Read in all partial symtabs on which this one is dependent */
  for (i = 0; i < pst->number_of_dependencies; i++)
    if (!pst->dependencies[i]->readin)
      {
	/* Inform about additional files that need to be read in.  */
	if (info_verbose)
	  {
	    fputs_filtered (" ", gdb_stdout);
	    wrap_here ("");
	    fputs_filtered ("and ", gdb_stdout);
	    wrap_here ("");
	    printf_filtered ("%s...", pst->dependencies[i]->filename);
	    wrap_here ("");	/* Flush output */
	    gdb_flush (gdb_stdout);
	  }
	xcoff_psymtab_to_symtab_1 (pst->dependencies[i]);
      }

  if (((struct symloc *) pst->read_symtab_private)->numsyms != 0)
    {
      /* Init stuff necessary for reading in symbols.  */
      stabsread_init ();
      buildsym_init ();
      old_chain = make_cleanup (really_free_pendings, 0);

      read_xcoff_symtab (pst);

      do_cleanups (old_chain);
    }

  pst->readin = 1;
}