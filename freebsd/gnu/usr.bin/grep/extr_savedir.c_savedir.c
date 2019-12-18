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
struct exclude {int dummy; } ;
struct dirent {char* d_name; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ CLOSEDIR (int /*<<< orphan*/ *) ; 
 int NAMLEN (struct dirent*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ excluded_filename (struct exclude*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isdir1 (char const*,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 char* path ; 
 scalar_t__ pathlen ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 char* realloc (char*,int) ; 
 char* stpcpy (char*,char*) ; 

char *
savedir (const char *dir, off_t name_size, struct exclude *included_patterns,
	 struct exclude *excluded_patterns)
{
  DIR *dirp;
  struct dirent *dp;
  char *name_space;
  char *namep;

  dirp = opendir (dir);
  if (dirp == NULL)
    return NULL;

  /* Be sure name_size is at least `1' so there's room for
     the final NUL byte.  */
  if (name_size <= 0)
    name_size = 1;

  name_space = (char *) malloc (name_size);
  if (name_space == NULL)
    {
      closedir (dirp);
      return NULL;
    }
  namep = name_space;

  while ((dp = readdir (dirp)) != NULL)
    {
      /* Skip "." and ".." (some NFS filesystems' directories lack them). */
      if (dp->d_name[0] != '.'
	  || (dp->d_name[1] != '\0'
	      && (dp->d_name[1] != '.' || dp->d_name[2] != '\0')))
	{
	  off_t size_needed = (namep - name_space) + NAMLEN (dp) + 2;

	  if ((included_patterns || excluded_patterns)
	      && !isdir1 (dir, dp->d_name))
	    {
	      if (included_patterns
		  && !excluded_filename (included_patterns, path, 0))
		continue;
	      if (excluded_patterns
		  && excluded_filename (excluded_patterns, path, 0))
		continue;
	    }

	  if (size_needed > name_size)
	    {
	      char *new_name_space;

	      while (size_needed > name_size)
		name_size += 1024;

	      new_name_space = realloc (name_space, name_size);
	      if (new_name_space == NULL)
		{
		  closedir (dirp);
		  return NULL;
		}
	      namep += new_name_space - name_space;
	      name_space = new_name_space;
	    }
	  namep = stpcpy (namep, dp->d_name) + 1;
	}
    }
  *namep = '\0';
  if (CLOSEDIR (dirp))
    {
      free (name_space);
      return NULL;
    }
  if (path)
    {
      free (path);
      path = NULL;
      pathlen = 0;
    }
  return name_space;
}