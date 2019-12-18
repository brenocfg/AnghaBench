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
struct objfile {char* name; } ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 char* DEBUG_SUBDIRECTORY ; 
 scalar_t__ IS_DIR_SEPARATOR (char) ; 
 char* alloca (int) ; 
 char* debug_file_directory ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 char* get_debug_link_info (struct objfile*,unsigned long*) ; 
 scalar_t__ separate_debug_file_exists (char*,unsigned long) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
find_separate_debug_file (struct objfile *objfile)
{
  asection *sect;
  char *basename;
  char *dir;
  char *debugfile;
  char *name_copy;
  bfd_size_type debuglink_size;
  unsigned long crc32;
  int i;

  basename = get_debug_link_info (objfile, &crc32);

  if (basename == NULL)
    return NULL;
  
  dir = xstrdup (objfile->name);

  /* Strip off the final filename part, leaving the directory name,
     followed by a slash.  Objfile names should always be absolute and
     tilde-expanded, so there should always be a slash in there
     somewhere.  */
  for (i = strlen(dir) - 1; i >= 0; i--)
    {
      if (IS_DIR_SEPARATOR (dir[i]))
	break;
    }
  gdb_assert (i >= 0 && IS_DIR_SEPARATOR (dir[i]));
  dir[i+1] = '\0';
  
  debugfile = alloca (strlen (debug_file_directory) + 1
                      + strlen (dir)
                      + strlen (DEBUG_SUBDIRECTORY)
                      + strlen ("/")
                      + strlen (basename) 
                      + 1);

  /* First try in the same directory as the original file.  */
  strcpy (debugfile, dir);
  strcat (debugfile, basename);

  if (separate_debug_file_exists (debugfile, crc32))
    {
      xfree (basename);
      xfree (dir);
      return xstrdup (debugfile);
    }
  
  /* Then try in the subdirectory named DEBUG_SUBDIRECTORY.  */
  strcpy (debugfile, dir);
  strcat (debugfile, DEBUG_SUBDIRECTORY);
  strcat (debugfile, "/");
  strcat (debugfile, basename);

  if (separate_debug_file_exists (debugfile, crc32))
    {
      xfree (basename);
      xfree (dir);
      return xstrdup (debugfile);
    }
  
  /* Then try in the global debugfile directory.  */
  strcpy (debugfile, debug_file_directory);
  strcat (debugfile, "/");
  strcat (debugfile, dir);
  strcat (debugfile, basename);

  if (separate_debug_file_exists (debugfile, crc32))
    {
      xfree (basename);
      xfree (dir);
      return xstrdup (debugfile);
    }
  
  xfree (basename);
  xfree (dir);
  return NULL;
}