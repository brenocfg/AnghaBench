#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stat {long st_mtime; } ;
struct section_offsets {int dummy; } ;
struct TYPE_10__ {scalar_t__ list; } ;
struct objfile {long mtime; int num_sections; int /*<<< orphan*/  flags; TYPE_2__* sf; struct section_offsets* section_offsets; int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/  name; void* macro_cache; void* psymbol_cache; int /*<<< orphan*/ * md; int /*<<< orphan*/ * fundamental_types; TYPE_3__ msymbol_demangled_hash; TYPE_3__ msymbol_hash; scalar_t__ minimal_symbol_count; int /*<<< orphan*/ * sym_private; int /*<<< orphan*/ * msymbols; int /*<<< orphan*/ * cp_namespace_symtab; int /*<<< orphan*/ * free_psymtabs; int /*<<< orphan*/ * psymtabs; int /*<<< orphan*/ * symtabs; int /*<<< orphan*/ * sections; int /*<<< orphan*/ * demangled_names_hash; TYPE_3__ static_psymbols; TYPE_3__ global_psymbols; TYPE_4__* obfd; struct objfile* next; } ;
struct cleanup {int dummy; } ;
struct TYPE_11__ {TYPE_1__* my_archive; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* sym_read ) (struct objfile*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sym_init ) (struct objfile*) ;int /*<<< orphan*/  (* sym_new_init ) (struct objfile*) ;int /*<<< orphan*/  (* sym_finish ) (struct objfile*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJF_SYMS ; 
 int /*<<< orphan*/  RESET_HP_UX_GLOBALS () ; 
 int /*<<< orphan*/  SIZEOF_N_SECTION_OFFSETS (int) ; 
 scalar_t__ alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcache_xfree (void*) ; 
 void* bcache_xmalloc () ; 
 int /*<<< orphan*/  bfd_check_format (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (TYPE_4__*) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 char* bfd_get_filename (TYPE_4__*) ; 
 int /*<<< orphan*/  bfd_object ; 
 TYPE_4__* bfd_openr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ build_objfile_section_table (struct objfile*) ; 
 int /*<<< orphan*/  clear_complaints (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  clear_objfile_data (struct objfile*) ; 
 int /*<<< orphan*/  clear_symtab_users () ; 
 int /*<<< orphan*/  clear_symtab_users_cleanup ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gnutarget ; 
 int /*<<< orphan*/  have_full_symbols () ; 
 int /*<<< orphan*/  have_partial_symbols () ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup_free_objfile (struct objfile*) ; 
 int /*<<< orphan*/  memcpy (struct section_offsets*,struct section_offsets*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 struct objfile* object_files ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int /*<<< orphan*/  reinit_frame_cache () ; 
 int /*<<< orphan*/  reread_separate_symbols (struct objfile*) ; 
 int stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  stub1 (struct objfile*) ; 
 int /*<<< orphan*/  stub2 (struct objfile*) ; 
 int /*<<< orphan*/  stub3 (struct objfile*) ; 
 int /*<<< orphan*/  stub4 (struct objfile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symfile_complaints ; 
 struct objfile* symfile_objfile ; 
 int /*<<< orphan*/  terminate_minimal_symbol_table (struct objfile*) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 
 int /*<<< orphan*/  xmfree (int /*<<< orphan*/ *,scalar_t__) ; 

void
reread_symbols (void)
{
  struct objfile *objfile;
  long new_modtime;
  int reread_one = 0;
  struct stat new_statbuf;
  int res;

  /* With the addition of shared libraries, this should be modified,
     the load time should be saved in the partial symbol tables, since
     different tables may come from different source files.  FIXME.
     This routine should then walk down each partial symbol table
     and see if the symbol table that it originates from has been changed */

  for (objfile = object_files; objfile; objfile = objfile->next)
    {
      if (objfile->obfd)
	{
#ifdef DEPRECATED_IBM6000_TARGET
	  /* If this object is from a shared library, then you should
	     stat on the library name, not member name. */

	  if (objfile->obfd->my_archive)
	    res = stat (objfile->obfd->my_archive->filename, &new_statbuf);
	  else
#endif
	    res = stat (objfile->name, &new_statbuf);
	  if (res != 0)
	    {
	      /* FIXME, should use print_sys_errmsg but it's not filtered. */
	      printf_unfiltered ("`%s' has disappeared; keeping its symbols.\n",
			       objfile->name);
	      continue;
	    }
	  new_modtime = new_statbuf.st_mtime;
	  if (new_modtime != objfile->mtime)
	    {
	      struct cleanup *old_cleanups;
	      struct section_offsets *offsets;
	      int num_offsets;
	      char *obfd_filename;

	      printf_unfiltered ("`%s' has changed; re-reading symbols.\n",
			       objfile->name);

	      /* There are various functions like symbol_file_add,
	         symfile_bfd_open, syms_from_objfile, etc., which might
	         appear to do what we want.  But they have various other
	         effects which we *don't* want.  So we just do stuff
	         ourselves.  We don't worry about mapped files (for one thing,
	         any mapped file will be out of date).  */

	      /* If we get an error, blow away this objfile (not sure if
	         that is the correct response for things like shared
	         libraries).  */
	      old_cleanups = make_cleanup_free_objfile (objfile);
	      /* We need to do this whenever any symbols go away.  */
	      make_cleanup (clear_symtab_users_cleanup, 0 /*ignore*/);

	      /* Clean up any state BFD has sitting around.  We don't need
	         to close the descriptor but BFD lacks a way of closing the
	         BFD without closing the descriptor.  */
	      obfd_filename = bfd_get_filename (objfile->obfd);
	      if (!bfd_close (objfile->obfd))
		error ("Can't close BFD for %s: %s", objfile->name,
		       bfd_errmsg (bfd_get_error ()));
	      objfile->obfd = bfd_openr (obfd_filename, gnutarget);
	      if (objfile->obfd == NULL)
		error ("Can't open %s to read symbols.", objfile->name);
	      /* bfd_openr sets cacheable to true, which is what we want.  */
	      if (!bfd_check_format (objfile->obfd, bfd_object))
		error ("Can't read symbols from %s: %s.", objfile->name,
		       bfd_errmsg (bfd_get_error ()));

	      /* Save the offsets, we will nuke them with the rest of the
	         objfile_obstack.  */
	      num_offsets = objfile->num_sections;
	      offsets = ((struct section_offsets *) 
			 alloca (SIZEOF_N_SECTION_OFFSETS (num_offsets)));
	      memcpy (offsets, objfile->section_offsets, 
		      SIZEOF_N_SECTION_OFFSETS (num_offsets));

	      /* Nuke all the state that we will re-read.  Much of the following
	         code which sets things to NULL really is necessary to tell
	         other parts of GDB that there is nothing currently there.  */

	      /* FIXME: Do we have to free a whole linked list, or is this
	         enough?  */
	      if (objfile->global_psymbols.list)
		xmfree (objfile->md, objfile->global_psymbols.list);
	      memset (&objfile->global_psymbols, 0,
		      sizeof (objfile->global_psymbols));
	      if (objfile->static_psymbols.list)
		xmfree (objfile->md, objfile->static_psymbols.list);
	      memset (&objfile->static_psymbols, 0,
		      sizeof (objfile->static_psymbols));

	      /* Free the obstacks for non-reusable objfiles */
	      bcache_xfree (objfile->psymbol_cache);
	      objfile->psymbol_cache = bcache_xmalloc ();
	      bcache_xfree (objfile->macro_cache);
	      objfile->macro_cache = bcache_xmalloc ();
	      if (objfile->demangled_names_hash != NULL)
		{
		  htab_delete (objfile->demangled_names_hash);
		  objfile->demangled_names_hash = NULL;
		}
	      obstack_free (&objfile->objfile_obstack, 0);
	      objfile->sections = NULL;
	      objfile->symtabs = NULL;
	      objfile->psymtabs = NULL;
	      objfile->free_psymtabs = NULL;
	      objfile->cp_namespace_symtab = NULL;
	      objfile->msymbols = NULL;
	      objfile->sym_private = NULL;
	      objfile->minimal_symbol_count = 0;
	      memset (&objfile->msymbol_hash, 0,
		      sizeof (objfile->msymbol_hash));
	      memset (&objfile->msymbol_demangled_hash, 0,
		      sizeof (objfile->msymbol_demangled_hash));
	      objfile->fundamental_types = NULL;
	      clear_objfile_data (objfile);
	      if (objfile->sf != NULL)
		{
		  (*objfile->sf->sym_finish) (objfile);
		}

	      /* We never make this a mapped file.  */
	      objfile->md = NULL;
	      objfile->psymbol_cache = bcache_xmalloc ();
	      objfile->macro_cache = bcache_xmalloc ();
	      /* obstack_init also initializes the obstack so it is
	         empty.  We could use obstack_specify_allocation but
	         gdb_obstack.h specifies the alloc/dealloc
	         functions.  */
	      obstack_init (&objfile->objfile_obstack);
	      if (build_objfile_section_table (objfile))
		{
		  error ("Can't find the file sections in `%s': %s",
			 objfile->name, bfd_errmsg (bfd_get_error ()));
		}
              terminate_minimal_symbol_table (objfile);

	      /* We use the same section offsets as from last time.  I'm not
	         sure whether that is always correct for shared libraries.  */
	      objfile->section_offsets = (struct section_offsets *)
		obstack_alloc (&objfile->objfile_obstack, 
			       SIZEOF_N_SECTION_OFFSETS (num_offsets));
	      memcpy (objfile->section_offsets, offsets, 
		      SIZEOF_N_SECTION_OFFSETS (num_offsets));
	      objfile->num_sections = num_offsets;

	      /* What the hell is sym_new_init for, anyway?  The concept of
	         distinguishing between the main file and additional files
	         in this way seems rather dubious.  */
	      if (objfile == symfile_objfile)
		{
		  (*objfile->sf->sym_new_init) (objfile);
#ifdef HPUXHPPA
		  RESET_HP_UX_GLOBALS ();
#endif
		}

	      (*objfile->sf->sym_init) (objfile);
	      clear_complaints (&symfile_complaints, 1, 1);
	      /* The "mainline" parameter is a hideous hack; I think leaving it
	         zero is OK since dbxread.c also does what it needs to do if
	         objfile->global_psymbols.size is 0.  */
	      (*objfile->sf->sym_read) (objfile, 0);
	      if (!have_partial_symbols () && !have_full_symbols ())
		{
		  wrap_here ("");
		  printf_unfiltered ("(no debugging symbols found)\n");
		  wrap_here ("");
		}
	      objfile->flags |= OBJF_SYMS;

	      /* We're done reading the symbol file; finish off complaints.  */
	      clear_complaints (&symfile_complaints, 0, 1);

	      /* Getting new symbols may change our opinion about what is
	         frameless.  */

	      reinit_frame_cache ();

	      /* Discard cleanups as symbol reading was successful.  */
	      discard_cleanups (old_cleanups);

	      /* If the mtime has changed between the time we set new_modtime
	         and now, we *want* this to be out of date, so don't call stat
	         again now.  */
	      objfile->mtime = new_modtime;
	      reread_one = 1;
              reread_separate_symbols (objfile);
	    }
	}
    }

  if (reread_one)
    clear_symtab_users ();
}