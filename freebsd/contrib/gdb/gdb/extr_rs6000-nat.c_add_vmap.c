#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct vmap {struct objfile* objfile; int /*<<< orphan*/  bfd; } ;
struct objfile {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ bfd ;
typedef  int /*<<< orphan*/  LdInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH64_DECL (int /*<<< orphan*/ ) ; 
 scalar_t__ DEPRECATED_STREQ (char*,int /*<<< orphan*/ ) ; 
 int LDI_FD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* LDI_FILENAME (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct objfile* allocate_objfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch64 ; 
 scalar_t__ auto_solib_add ; 
 int /*<<< orphan*/  bfd_archive ; 
 scalar_t__ bfd_check_format (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (TYPE_1__*) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 TYPE_1__* bfd_fdopenr (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_object ; 
 TYPE_1__* bfd_openr (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* bfd_openr_next_archived_file (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gnutarget ; 
 struct vmap* map_vmap (TYPE_1__*,TYPE_1__*) ; 
 char* savestring (char*,int) ; 
 int strlen (char*) ; 
 struct vmap* vmap ; 
 int /*<<< orphan*/  vmap_add_symbols (struct vmap*) ; 
 int /*<<< orphan*/  warning (char*,char*,char*,...) ; 

__attribute__((used)) static struct vmap *
add_vmap (LdInfo *ldi)
{
  bfd *abfd, *last;
  char *mem, *objname, *filename;
  struct objfile *obj;
  struct vmap *vp;
  int fd;
  ARCH64_DECL (arch64);

  /* This ldi structure was allocated using alloca() in 
     xcoff_relocate_symtab(). Now we need to have persistent object 
     and member names, so we should save them. */

  filename = LDI_FILENAME (ldi, arch64);
  mem = filename + strlen (filename) + 1;
  mem = savestring (mem, strlen (mem));
  objname = savestring (filename, strlen (filename));

  fd = LDI_FD (ldi, arch64);
  if (fd < 0)
    /* Note that this opens it once for every member; a possible
       enhancement would be to only open it once for every object.  */
    abfd = bfd_openr (objname, gnutarget);
  else
    abfd = bfd_fdopenr (objname, gnutarget, fd);
  if (!abfd)
    {
      warning ("Could not open `%s' as an executable file: %s",
	       objname, bfd_errmsg (bfd_get_error ()));
      return NULL;
    }

  /* make sure we have an object file */

  if (bfd_check_format (abfd, bfd_object))
    vp = map_vmap (abfd, 0);

  else if (bfd_check_format (abfd, bfd_archive))
    {
      last = 0;
      /* FIXME??? am I tossing BFDs?  bfd? */
      while ((last = bfd_openr_next_archived_file (abfd, last)))
	if (DEPRECATED_STREQ (mem, last->filename))
	  break;

      if (!last)
	{
	  warning ("\"%s\": member \"%s\" missing.", objname, mem);
	  bfd_close (abfd);
	  return NULL;
	}

      if (!bfd_check_format (last, bfd_object))
	{
	  warning ("\"%s\": member \"%s\" not in executable format: %s.",
		   objname, mem, bfd_errmsg (bfd_get_error ()));
	  bfd_close (last);
	  bfd_close (abfd);
	  return NULL;
	}

      vp = map_vmap (last, abfd);
    }
  else
    {
      warning ("\"%s\": not in executable format: %s.",
	       objname, bfd_errmsg (bfd_get_error ()));
      bfd_close (abfd);
      return NULL;
    }
  obj = allocate_objfile (vp->bfd, 0);
  vp->objfile = obj;

  /* Always add symbols for the main objfile.  */
  if (vp == vmap || auto_solib_add)
    vmap_add_symbols (vp);
  return vp;
}