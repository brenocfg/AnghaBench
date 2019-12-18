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
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
typedef  int LONGEST ;

/* Variables and functions */
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_fdopenr (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_object ; 
 scalar_t__ bfd_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  gnutarget ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/  (*) (char*),char*) ; 
 int openp (int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static LONGEST
som_solib_sizeof_symbol_table (char *filename)
{
  bfd *abfd;
  int desc;
  char *absolute_name;
  LONGEST st_size = (LONGEST) 0;
  asection *sect;

  /* We believe that filename was handed to us by the dynamic linker, and
     is therefore always an absolute path.
   */
  desc = openp (getenv ("PATH"), 1, filename, O_RDONLY | O_BINARY, 0, &absolute_name);
  if (desc < 0)
    {
      perror_with_name (filename);
    }
  filename = absolute_name;

  abfd = bfd_fdopenr (filename, gnutarget, desc);
  if (!abfd)
    {
      close (desc);
      make_cleanup (xfree, filename);
      error ("\"%s\": can't open to read symbols: %s.", filename,
	     bfd_errmsg (bfd_get_error ()));
    }

  if (!bfd_check_format (abfd, bfd_object))	/* Reads in section info */
    {
      bfd_close (abfd);		/* This also closes desc */
      make_cleanup (xfree, filename);
      error ("\"%s\": can't read symbols: %s.", filename,
	     bfd_errmsg (bfd_get_error ()));
    }

  /* Sum the sizes of the various sections that compose debug info. */

  /* This contains non-DOC information. */
  sect = bfd_get_section_by_name (abfd, "$DEBUG$");
  if (sect)
    st_size += (LONGEST) bfd_section_size (abfd, sect);

  /* This contains DOC information. */
  sect = bfd_get_section_by_name (abfd, "$PINFO$");
  if (sect)
    st_size += (LONGEST) bfd_section_size (abfd, sect);

  bfd_close (abfd);		/* This also closes desc */
  xfree (filename);

  /* Unfortunately, just summing the sizes of various debug info
     sections isn't a very accurate measurement of how much heap
     space the debugger will need to hold them.  It also doesn't
     account for space needed by linker (aka "minimal") symbols.

     Anecdotal evidence suggests that just summing the sizes of
     debug-info-related sections understates the heap space needed
     to represent it internally by about an order of magnitude.

     Since it's not exactly brain surgery we're doing here, rather
     than attempt to more accurately measure the size of a shlib's
     symbol table in GDB's heap, we'll just apply a 10x fudge-
     factor to the debug info sections' size-sum.  No, this doesn't
     account for minimal symbols in non-debuggable shlibs.  But it
     all roughly washes out in the end.
   */
  return st_size * (LONGEST) 10;
}