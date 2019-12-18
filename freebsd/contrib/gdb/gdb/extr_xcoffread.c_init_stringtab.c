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
struct objfile {scalar_t__ sym_private; int /*<<< orphan*/  objfile_obstack; } ;
struct coff_symfile_info {char* strtbl; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int bfd_bread (char*,int,int /*<<< orphan*/ *) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 long bfd_h_get_32 (int /*<<< orphan*/ *,unsigned char*) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,int) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,long) ; 

__attribute__((used)) static void
init_stringtab (bfd *abfd, file_ptr offset, struct objfile *objfile)
{
  long length;
  int val;
  unsigned char lengthbuf[4];
  char *strtbl;

  ((struct coff_symfile_info *) objfile->sym_private)->strtbl = NULL;

  if (bfd_seek (abfd, offset, SEEK_SET) < 0)
    error ("cannot seek to string table in %s: %s",
	   bfd_get_filename (abfd), bfd_errmsg (bfd_get_error ()));

  val = bfd_bread ((char *) lengthbuf, sizeof lengthbuf, abfd);
  length = bfd_h_get_32 (abfd, lengthbuf);

  /* If no string table is needed, then the file may end immediately
     after the symbols.  Just return with `strtbl' set to NULL.  */

  if (val != sizeof lengthbuf || length < sizeof lengthbuf)
    return;

  /* Allocate string table from objfile_obstack. We will need this table
     as long as we have its symbol table around. */

  strtbl = (char *) obstack_alloc (&objfile->objfile_obstack, length);
  ((struct coff_symfile_info *) objfile->sym_private)->strtbl = strtbl;

  /* Copy length buffer, the first byte is usually zero and is
     used for stabs with a name length of zero.  */
  memcpy (strtbl, lengthbuf, sizeof lengthbuf);
  if (length == sizeof lengthbuf)
    return;

  val = bfd_bread (strtbl + sizeof lengthbuf, length - sizeof lengthbuf, abfd);

  if (val != length - sizeof lengthbuf)
    error ("cannot read string table from %s: %s",
	   bfd_get_filename (abfd), bfd_errmsg (bfd_get_error ()));
  if (strtbl[length - 1] != '\0')
    error ("bad symbol file: string table does not end with null character");

  return;
}