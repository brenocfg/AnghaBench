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
struct section_offsets {int dummy; } ;
struct section_addr_info {int num_sections; int /*<<< orphan*/ * other; } ;
struct partial_symtab {struct partial_symtab* next; } ;
struct objfile {int /*<<< orphan*/ * sf; TYPE_1__* separate_debug_objfile; struct partial_symtab* psymtabs; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {struct objfile* separate_debug_objfile_backlink; } ;

/* Variables and functions */
 int OBJF_READNOW ; 
 struct section_addr_info* alloc_section_addr_info (int /*<<< orphan*/ ) ; 
 struct objfile* allocate_objfile (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfd_count_sections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 char* find_separate_debug_file (struct objfile*) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ have_full_symbols () ; 
 scalar_t__ have_partial_symbols () ; 
 scalar_t__ info_verbose ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/  (*) (char*),struct section_addr_info*) ; 
 int /*<<< orphan*/  new_symfile_objfile (struct objfile*,int,int) ; 
 int /*<<< orphan*/  post_add_symbol_hook () ; 
 int /*<<< orphan*/  pre_add_symbol_hook (char*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int /*<<< orphan*/  psymtab_to_symtab (struct partial_symtab*) ; 
 int /*<<< orphan*/  put_objfile_before (TYPE_1__*,struct objfile*) ; 
 int /*<<< orphan*/  query (char*,char*) ; 
 scalar_t__ readnow_symbol_files ; 
 void* symbol_file_add (char*,int,struct section_addr_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * symfile_bfd_open (char*) ; 
 int /*<<< orphan*/  syms_from_objfile (struct objfile*,struct section_addr_info*,struct section_offsets*,int,int,int) ; 
 int /*<<< orphan*/  target_new_objfile_hook (struct objfile*) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static struct objfile *
symbol_file_add_with_addrs_or_offsets (char *name, int from_tty,
                                       struct section_addr_info *addrs,
                                       struct section_offsets *offsets,
                                       int num_offsets,
                                       int mainline, int flags)
{
  struct objfile *objfile;
  struct partial_symtab *psymtab;
  char *debugfile;
  bfd *abfd;
  struct section_addr_info *orig_addrs;
  struct cleanup *my_cleanups;

  /* Open a bfd for the file, and give user a chance to burp if we'd be
     interactively wiping out any existing symbols.  */

  abfd = symfile_bfd_open (name);

  if ((have_full_symbols () || have_partial_symbols ())
      && mainline
      && from_tty
      && !query ("Load new symbol table from \"%s\"? ", name))
    error ("Not confirmed.");

  objfile = allocate_objfile (abfd, flags);

  orig_addrs = alloc_section_addr_info (bfd_count_sections (abfd));
  my_cleanups = make_cleanup (xfree, orig_addrs);
  if (addrs)
    {
      int i;
      orig_addrs->num_sections = addrs->num_sections;
      for (i = 0; i < addrs->num_sections; i++)
	orig_addrs->other[i] = addrs->other[i];
    }

  /* We either created a new mapped symbol table, mapped an existing
     symbol table file which has not had initial symbol reading
     performed, or need to read an unmapped symbol table. */
  if (from_tty || info_verbose)
    {
      if (pre_add_symbol_hook)
	pre_add_symbol_hook (name);
      else
	{
	  printf_unfiltered ("Reading symbols from %s...", name);
	  wrap_here ("");
	  gdb_flush (gdb_stdout);
	}
    }
  syms_from_objfile (objfile, addrs, offsets, num_offsets,
		     mainline, from_tty);

  /* We now have at least a partial symbol table.  Check to see if the
     user requested that all symbols be read on initial access via either
     the gdb startup command line or on a per symbol file basis.  Expand
     all partial symbol tables for this objfile if so. */

  if ((flags & OBJF_READNOW) || readnow_symbol_files)
    {
      if (from_tty || info_verbose)
	{
	  printf_unfiltered ("expanding to full symbols...");
	  wrap_here ("");
	  gdb_flush (gdb_stdout);
	}

      for (psymtab = objfile->psymtabs;
	   psymtab != NULL;
	   psymtab = psymtab->next)
	{
	  psymtab_to_symtab (psymtab);
	}
    }

  debugfile = find_separate_debug_file (objfile);
  if (debugfile)
    {
      if (addrs != NULL)
	{
	  objfile->separate_debug_objfile
            = symbol_file_add (debugfile, from_tty, orig_addrs, 0, flags);
	}
      else
	{
	  objfile->separate_debug_objfile
            = symbol_file_add (debugfile, from_tty, NULL, 0, flags);
	}
      objfile->separate_debug_objfile->separate_debug_objfile_backlink
        = objfile;
      
      /* Put the separate debug object before the normal one, this is so that
         usage of the ALL_OBJFILES_SAFE macro will stay safe. */
      put_objfile_before (objfile->separate_debug_objfile, objfile);
      
      xfree (debugfile);
    }
  
  if (!have_partial_symbols () && !have_full_symbols ())
    {
      wrap_here ("");
      printf_unfiltered ("(no debugging symbols found)...");
      wrap_here ("");
    }

  if (from_tty || info_verbose)
    {
      if (post_add_symbol_hook)
	post_add_symbol_hook ();
      else
	{
	  printf_unfiltered ("done.\n");
	}
    }

  /* We print some messages regardless of whether 'from_tty ||
     info_verbose' is true, so make sure they go out at the right
     time.  */
  gdb_flush (gdb_stdout);

  do_cleanups (my_cleanups);

  if (objfile->sf == NULL)
    return objfile;	/* No symbols. */

  new_symfile_objfile (objfile, mainline, from_tty);

  if (target_new_objfile_hook)
    target_new_objfile_hook (objfile);

  return (objfile);
}