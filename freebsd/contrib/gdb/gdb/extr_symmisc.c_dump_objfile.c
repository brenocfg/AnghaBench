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
struct symtab {struct symtab* objfile; int /*<<< orphan*/  filename; struct symtab* next; struct symtab* symtabs; struct symtab* psymtabs; int /*<<< orphan*/  minimal_symbol_count; struct symtab* obfd; int /*<<< orphan*/  name; } ;
struct partial_symtab {struct partial_symtab* objfile; int /*<<< orphan*/  filename; struct partial_symtab* next; struct partial_symtab* symtabs; struct partial_symtab* psymtabs; int /*<<< orphan*/  minimal_symbol_count; struct partial_symtab* obfd; int /*<<< orphan*/  name; } ;
struct objfile {struct objfile* objfile; int /*<<< orphan*/  filename; struct objfile* next; struct objfile* symtabs; struct objfile* psymtabs; int /*<<< orphan*/  minimal_symbol_count; struct objfile* obfd; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_print_host_address (struct symtab*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
dump_objfile (struct objfile *objfile)
{
  struct symtab *symtab;
  struct partial_symtab *psymtab;

  printf_filtered ("\nObject file %s:  ", objfile->name);
  printf_filtered ("Objfile at ");
  gdb_print_host_address (objfile, gdb_stdout);
  printf_filtered (", bfd at ");
  gdb_print_host_address (objfile->obfd, gdb_stdout);
  printf_filtered (", %d minsyms\n\n",
		   objfile->minimal_symbol_count);

  if (objfile->psymtabs)
    {
      printf_filtered ("Psymtabs:\n");
      for (psymtab = objfile->psymtabs;
	   psymtab != NULL;
	   psymtab = psymtab->next)
	{
	  printf_filtered ("%s at ",
			   psymtab->filename);
	  gdb_print_host_address (psymtab, gdb_stdout);
	  printf_filtered (", ");
	  if (psymtab->objfile != objfile)
	    {
	      printf_filtered ("NOT ON CHAIN!  ");
	    }
	  wrap_here ("  ");
	}
      printf_filtered ("\n\n");
    }

  if (objfile->symtabs)
    {
      printf_filtered ("Symtabs:\n");
      for (symtab = objfile->symtabs;
	   symtab != NULL;
	   symtab = symtab->next)
	{
	  printf_filtered ("%s at ", symtab->filename);
	  gdb_print_host_address (symtab, gdb_stdout);
	  printf_filtered (", ");
	  if (symtab->objfile != objfile)
	    {
	      printf_filtered ("NOT ON CHAIN!  ");
	    }
	  wrap_here ("  ");
	}
      printf_filtered ("\n\n");
    }
}