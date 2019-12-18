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
struct TYPE_5__ {scalar_t__ size; } ;
struct TYPE_4__ {scalar_t__ size; } ;
struct objfile {char* name; TYPE_2__ static_psymbols; TYPE_1__ global_psymbols; scalar_t__ sym_private; int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/ * obfd; } ;
struct coff_symfile_info {char* debugsec; int symtbl_num_syms; scalar_t__ symtbl; scalar_t__ max_lineno_offset; scalar_t__ min_lineno_offset; } ;
struct cleanup {int dummy; } ;
struct bfd_section {int dummy; } ;
typedef  scalar_t__ file_ptr ;
typedef  unsigned int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int local_symesz; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int bfd_bread (scalar_t__,unsigned int,int /*<<< orphan*/ *) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 struct bfd_section* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,struct bfd_section*,char*,scalar_t__,unsigned int) ; 
 int bfd_get_symcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct coff_symfile_info*) ; 
 unsigned int bfd_section_size (int /*<<< orphan*/ *,struct bfd_section*) ; 
 int bfd_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* coff_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  find_linenos ; 
 int /*<<< orphan*/  free_pending_blocks () ; 
 int /*<<< orphan*/  init_minimal_symbol_collection () ; 
 int /*<<< orphan*/  init_psymbol_list (struct objfile*,int) ; 
 int /*<<< orphan*/  init_stringtab (int /*<<< orphan*/ *,scalar_t__,struct objfile*) ; 
 int /*<<< orphan*/  install_minimal_symbols (struct objfile*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_cleanup_discard_minimal_symbols () ; 
 scalar_t__ obj_sym_filepos (int /*<<< orphan*/ *) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  really_free_pendings ; 
 int /*<<< orphan*/  scan_xcoff_symtab (struct objfile*) ; 
 int /*<<< orphan*/ * symfile_bfd ; 

__attribute__((used)) static void
xcoff_initial_scan (struct objfile *objfile, int mainline)
{
  bfd *abfd;
  int val;
  struct cleanup *back_to;
  int num_symbols;		/* # of symbols */
  file_ptr symtab_offset;	/* symbol table and */
  file_ptr stringtab_offset;	/* string table file offsets */
  struct coff_symfile_info *info;
  char *name;
  unsigned int size;

  info = (struct coff_symfile_info *) objfile->sym_private;
  symfile_bfd = abfd = objfile->obfd;
  name = objfile->name;

  num_symbols = bfd_get_symcount (abfd);	/* # of symbols */
  symtab_offset = obj_sym_filepos (abfd);	/* symbol table file offset */
  stringtab_offset = symtab_offset +
    num_symbols * coff_data (abfd)->local_symesz;

  info->min_lineno_offset = 0;
  info->max_lineno_offset = 0;
  bfd_map_over_sections (abfd, find_linenos, info);

  if (num_symbols > 0)
    {
      /* Read the string table.  */
      init_stringtab (abfd, stringtab_offset, objfile);

      /* Read the .debug section, if present.  */
      {
	struct bfd_section *secp;
	bfd_size_type length;
	char *debugsec = NULL;

	secp = bfd_get_section_by_name (abfd, ".debug");
	if (secp)
	  {
	    length = bfd_section_size (abfd, secp);
	    if (length)
	      {
		debugsec =
		  (char *) obstack_alloc (&objfile->objfile_obstack, length);

		if (!bfd_get_section_contents (abfd, secp, debugsec,
					       (file_ptr) 0, length))
		  {
		    error ("Error reading .debug section of `%s': %s",
			   name, bfd_errmsg (bfd_get_error ()));
		  }
	      }
	  }
	((struct coff_symfile_info *) objfile->sym_private)->debugsec =
	  debugsec;
      }
    }

  /* Read the symbols.  We keep them in core because we will want to
     access them randomly in read_symbol*.  */
  val = bfd_seek (abfd, symtab_offset, SEEK_SET);
  if (val < 0)
    error ("Error reading symbols from %s: %s",
	   name, bfd_errmsg (bfd_get_error ()));
  size = coff_data (abfd)->local_symesz * num_symbols;
  ((struct coff_symfile_info *) objfile->sym_private)->symtbl =
    obstack_alloc (&objfile->objfile_obstack, size);
  ((struct coff_symfile_info *) objfile->sym_private)->symtbl_num_syms =
    num_symbols;

  val = bfd_bread (((struct coff_symfile_info *) objfile->sym_private)->symtbl,
		   size, abfd);
  if (val != size)
    perror_with_name ("reading symbol table");

  /* If we are reinitializing, or if we have never loaded syms yet, init */
  if (mainline
      || (objfile->global_psymbols.size == 0
	  && objfile->static_psymbols.size == 0))
    /* I'm not sure how how good num_symbols is; the rule of thumb in
       init_psymbol_list was developed for a.out.  On the one hand,
       num_symbols includes auxents.  On the other hand, it doesn't
       include N_SLINE.  */
    init_psymbol_list (objfile, num_symbols);

  free_pending_blocks ();
  back_to = make_cleanup (really_free_pendings, 0);

  init_minimal_symbol_collection ();
  make_cleanup_discard_minimal_symbols ();

  /* Now that the symbol table data of the executable file are all in core,
     process them and define symbols accordingly.  */

  scan_xcoff_symtab (objfile);

  /* Install any minimal symbols that have been collected as the current
     minimal symbols for this objfile. */

  install_minimal_symbols (objfile);

  do_cleanups (back_to);
}