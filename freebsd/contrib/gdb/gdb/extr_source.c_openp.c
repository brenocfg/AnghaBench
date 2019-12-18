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

/* Variables and functions */
 int /*<<< orphan*/  DIRNAME_SEPARATOR ; 
 scalar_t__ IS_ABSOLUTE_PATH (char const*) ; 
 scalar_t__ IS_DIR_SEPARATOR (char const) ; 
 int O_BINARY ; 
 char* SLASH_STRING ; 
 char* alloca (int) ; 
 char* concat (char*,char*,char*,int /*<<< orphan*/ *) ; 
 char* current_directory ; 
 scalar_t__ is_regular_file (char const*) ; 
 int open (char*,int,...) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xfullpath (char*) ; 

int
openp (const char *path, int try_cwd_first, const char *string,
       int mode, int prot,
       char **filename_opened)
{
  int fd;
  char *filename;
  const char *p;
  const char *p1;
  int len;
  int alloclen;

  if (!path)
    path = ".";

#if defined(_WIN32) || defined(__CYGWIN__)
  mode |= O_BINARY;
#endif

  if (try_cwd_first || IS_ABSOLUTE_PATH (string))
    {
      int i;

      if (is_regular_file (string))
	{
	  filename = alloca (strlen (string) + 1);
	  strcpy (filename, string);
	  fd = open (filename, mode, prot);
	  if (fd >= 0)
	    goto done;
	}
      else
	{
	  filename = NULL;
	  fd = -1;
	}

      for (i = 0; string[i]; i++)
	if (IS_DIR_SEPARATOR (string[i]))
	  goto done;
    }

  /* ./foo => foo */
  while (string[0] == '.' && IS_DIR_SEPARATOR (string[1]))
    string += 2;

  alloclen = strlen (path) + strlen (string) + 2;
  filename = alloca (alloclen);
  fd = -1;
  for (p = path; p; p = p1 ? p1 + 1 : 0)
    {
      p1 = strchr (p, DIRNAME_SEPARATOR);
      if (p1)
	len = p1 - p;
      else
	len = strlen (p);

      if (len == 4 && p[0] == '$' && p[1] == 'c'
	  && p[2] == 'w' && p[3] == 'd')
	{
	  /* Name is $cwd -- insert current directory name instead.  */
	  int newlen;

	  /* First, realloc the filename buffer if too short. */
	  len = strlen (current_directory);
	  newlen = len + strlen (string) + 2;
	  if (newlen > alloclen)
	    {
	      alloclen = newlen;
	      filename = alloca (alloclen);
	    }
	  strcpy (filename, current_directory);
	}
      else
	{
	  /* Normal file name in path -- just use it.  */
	  strncpy (filename, p, len);
	  filename[len] = 0;
	}

      /* Remove trailing slashes */
      while (len > 0 && IS_DIR_SEPARATOR (filename[len - 1]))
	filename[--len] = 0;

      strcat (filename + len, SLASH_STRING);
      strcat (filename, string);

      if (is_regular_file (filename))
      {
        fd = open (filename, mode);
        if (fd >= 0)
          break;
      }
    }

done:
  if (filename_opened)
    {
      /* If a file was opened, canonicalize its filename. Use xfullpath
         rather than gdb_realpath to avoid resolving the basename part
         of filenames when the associated file is a symbolic link. This
         fixes a potential inconsistency between the filenames known to
         GDB and the filenames it prints in the annotations.  */
      if (fd < 0)
	*filename_opened = NULL;
      else if (IS_ABSOLUTE_PATH (filename))
	*filename_opened = xfullpath (filename);
      else
	{
	  /* Beware the // my son, the Emacs barfs, the botch that catch... */

	  char *f = concat (current_directory,
           IS_DIR_SEPARATOR (current_directory[strlen (current_directory) - 1])
				     ? "" : SLASH_STRING,
				     filename, NULL);
	  *filename_opened = xfullpath (f);
	  xfree (f);
	}
    }

  return fd;
}