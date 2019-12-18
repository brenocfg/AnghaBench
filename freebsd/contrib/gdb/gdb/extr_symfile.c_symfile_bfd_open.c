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

/* Variables and functions */
 int O_BINARY ; 
 int O_RDONLY ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_fdopenr (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/  bfd_set_cacheable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  gnutarget ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/  (*) (char*),char*) ; 
 int openp (int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* tilde_expand (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

bfd *
symfile_bfd_open (char *name)
{
  bfd *sym_bfd;
  int desc;
  char *absolute_name;



  name = tilde_expand (name);	/* Returns 1st new malloc'd copy */

  /* Look down path for it, allocate 2nd new malloc'd copy.  */
  desc = openp (getenv ("PATH"), 1, name, O_RDONLY | O_BINARY, 0, &absolute_name);
#if defined(__GO32__) || defined(_WIN32) || defined (__CYGWIN__)
  if (desc < 0)
    {
      char *exename = alloca (strlen (name) + 5);
      strcat (strcpy (exename, name), ".exe");
      desc = openp (getenv ("PATH"), 1, exename, O_RDONLY | O_BINARY,
		    0, &absolute_name);
    }
#endif
  if (desc < 0)
    {
      make_cleanup (xfree, name);
      perror_with_name (name);
    }
  xfree (name);			/* Free 1st new malloc'd copy */
  name = absolute_name;		/* Keep 2nd malloc'd copy in bfd */
  /* It'll be freed in free_objfile(). */

  sym_bfd = bfd_fdopenr (name, gnutarget, desc);
  if (!sym_bfd)
    {
      close (desc);
      make_cleanup (xfree, name);
      error ("\"%s\": can't open to read symbols: %s.", name,
	     bfd_errmsg (bfd_get_error ()));
    }
  bfd_set_cacheable (sym_bfd, 1);

  if (!bfd_check_format (sym_bfd, bfd_object))
    {
      /* FIXME: should be checking for errors from bfd_close (for one thing,
         on error it does not free all the storage associated with the
         bfd).  */
      bfd_close (sym_bfd);	/* This also closes desc */
      make_cleanup (xfree, name);
      error ("\"%s\": can't read symbols: %s.", name,
	     bfd_errmsg (bfd_get_error ()));
    }
  return (sym_bfd);
}