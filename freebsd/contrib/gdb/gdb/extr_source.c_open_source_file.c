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
struct symtab {char* fullname; char const* dirname; char const* filename; TYPE_1__* objfile; } ;
struct TYPE_2__ {int /*<<< orphan*/  md; } ;

/* Variables and functions */
 char const DIRNAME_SEPARATOR ; 
 int /*<<< orphan*/  OPEN_MODE ; 
 scalar_t__ alloca (scalar_t__) ; 
 size_t cdir_len ; 
 char* lbasename (char const*) ; 
 char* mstrsave (int /*<<< orphan*/ ,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int openp (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 char const* source_path ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 scalar_t__ strstr (char const*,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 int /*<<< orphan*/  xmfree (int /*<<< orphan*/ ,char*) ; 

int
open_source_file (struct symtab *s)
{
  char *path = source_path;
  const char *p;
  int result;
  char *fullname;

  /* Quick way out if we already know its full name */
  if (s->fullname)
    {
      result = open (s->fullname, OPEN_MODE);
      if (result >= 0)
	return result;
      /* Didn't work -- free old one, try again. */
      xmfree (s->objfile->md, s->fullname);
      s->fullname = NULL;
    }

  if (s->dirname != NULL)
    {
      /* Replace a path entry of  $cdir  with the compilation directory name */
#define	cdir_len	5
      /* We cast strstr's result in case an ANSIhole has made it const,
         which produces a "required warning" when assigned to a nonconst. */
      p = (char *) strstr (source_path, "$cdir");
      if (p && (p == path || p[-1] == DIRNAME_SEPARATOR)
	  && (p[cdir_len] == DIRNAME_SEPARATOR || p[cdir_len] == '\0'))
	{
	  int len;

	  path = (char *)
	    alloca (strlen (source_path) + 1 + strlen (s->dirname) + 1);
	  len = p - source_path;
	  strncpy (path, source_path, len);	/* Before $cdir */
	  strcpy (path + len, s->dirname);	/* new stuff */
	  strcat (path + len, source_path + len + cdir_len);	/* After $cdir */
	}
    }

  result = openp (path, 0, s->filename, OPEN_MODE, 0, &s->fullname);
  if (result < 0)
    {
      /* Didn't work.  Try using just the basename. */
      p = lbasename (s->filename);
      if (p != s->filename)
	result = openp (path, 0, p, OPEN_MODE, 0, &s->fullname);
    }

  if (result >= 0)
    {
      fullname = s->fullname;
      s->fullname = mstrsave (s->objfile->md, s->fullname);
      xfree (fullname);
    }
  return result;
}