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
struct so_list {struct section_table* textsection; struct section_table* sections_end; struct section_table* sections; int /*<<< orphan*/  so_name; int /*<<< orphan*/ * abfd; } ;
struct section_table {TYPE_1__* the_bfd_section; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ SO_NAME_MAX_PATH_SIZE ; 
 int /*<<< orphan*/  TARGET_SO_RELOCATE_SECTION_ADDRESSES (struct so_list*,struct section_table*) ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_fdopenr (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/  bfd_set_cacheable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ build_section_table (int /*<<< orphan*/ *,struct section_table**,struct section_table**) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  gnutarget ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int solib_open (char*,char**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* tilde_expand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static int
solib_map_sections (void *arg)
{
  struct so_list *so = (struct so_list *) arg;	/* catch_errors bogon */
  char *filename;
  char *scratch_pathname;
  int scratch_chan;
  struct section_table *p;
  struct cleanup *old_chain;
  bfd *abfd;

  filename = tilde_expand (so->so_name);

  old_chain = make_cleanup (xfree, filename);
  scratch_chan = solib_open (filename, &scratch_pathname);

  if (scratch_chan < 0)
    {
      perror_with_name (filename);
    }

  /* Leave scratch_pathname allocated.  abfd->name will point to it.  */
  abfd = bfd_fdopenr (scratch_pathname, gnutarget, scratch_chan);
  if (!abfd)
    {
      close (scratch_chan);
      error ("Could not open `%s' as an executable file: %s",
	     scratch_pathname, bfd_errmsg (bfd_get_error ()));
    }

  /* Leave bfd open, core_xfer_memory and "info files" need it.  */
  so->abfd = abfd;
  bfd_set_cacheable (abfd, 1);

  /* copy full path name into so_name, so that later symbol_file_add
     can find it */
  if (strlen (scratch_pathname) >= SO_NAME_MAX_PATH_SIZE)
    error ("Full path name length of shared library exceeds SO_NAME_MAX_PATH_SIZE in so_list structure.");
  strcpy (so->so_name, scratch_pathname);

  if (!bfd_check_format (abfd, bfd_object))
    {
      error ("\"%s\": not in executable format: %s.",
	     scratch_pathname, bfd_errmsg (bfd_get_error ()));
    }
  if (build_section_table (abfd, &so->sections, &so->sections_end))
    {
      error ("Can't find the file sections in `%s': %s",
	     bfd_get_filename (abfd), bfd_errmsg (bfd_get_error ()));
    }

  for (p = so->sections; p < so->sections_end; p++)
    {
      /* Relocate the section binding addresses as recorded in the shared
         object's file by the base address to which the object was actually
         mapped. */
      TARGET_SO_RELOCATE_SECTION_ADDRESSES (so, p);
      if (strcmp (p->the_bfd_section->name, ".text") == 0)
	{
	  so->textsection = p;
	}
    }

  /* Free the file names, close the file now.  */
  do_cleanups (old_chain);

  return (1);
}