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
 scalar_t__ IS_ABSOLUTE_PATH (char*) ; 
 scalar_t__ IS_DIR_SEPARATOR (char) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int TARGET_SO_FIND_AND_OPEN_SOLIB (char*,int /*<<< orphan*/ ,char**) ; 
 char* alloca (int) ; 
 int /*<<< orphan*/ * get_in_environ (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  inferior_environ ; 
 char* lbasename (char*) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int openp (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 char* solib_absolute_prefix ; 
 int /*<<< orphan*/ * solib_search_path ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* xstrdup (char*) ; 

int
solib_open (char *in_pathname, char **found_pathname)
{
  int found_file = -1;
  char *temp_pathname = NULL;
  char *p = in_pathname;

  while (*p && !IS_DIR_SEPARATOR (*p))
    p++;

  if (*p)
    {
      if (! IS_ABSOLUTE_PATH (in_pathname) || solib_absolute_prefix == NULL)
        temp_pathname = in_pathname;
      else
	{
	  int prefix_len = strlen (solib_absolute_prefix);

	  /* Remove trailing slashes from absolute prefix.  */
	  while (prefix_len > 0
		 && IS_DIR_SEPARATOR (solib_absolute_prefix[prefix_len - 1]))
	    prefix_len--;

	  /* Cat the prefixed pathname together.  */
	  temp_pathname = alloca (prefix_len + strlen (in_pathname) + 1);
	  strncpy (temp_pathname, solib_absolute_prefix, prefix_len);
	  temp_pathname[prefix_len] = '\0';
	  strcat (temp_pathname, in_pathname);
	}

      /* Now see if we can open it.  */
      found_file = open (temp_pathname, O_RDONLY, 0);
    }

  /* If the search in solib_absolute_prefix failed, and the path name is
     absolute at this point, make it relative.  (openp will try and open the
     file according to its absolute path otherwise, which is not what we want.)
     Affects subsequent searches for this solib.  */
  if (found_file < 0 && IS_ABSOLUTE_PATH (in_pathname))
    {
      /* First, get rid of any drive letters etc.  */
      while (!IS_DIR_SEPARATOR (*in_pathname))
        in_pathname++;

      /* Next, get rid of all leading dir separators.  */
      while (IS_DIR_SEPARATOR (*in_pathname))
        in_pathname++;
    }
  
  /* If not found, search the solib_search_path (if any).  */
  if (found_file < 0 && solib_search_path != NULL)
    found_file = openp (solib_search_path,
			1, in_pathname, O_RDONLY, 0, &temp_pathname);
  
  /* If not found, next search the solib_search_path (if any) for the basename
     only (ignoring the path).  This is to allow reading solibs from a path
     that differs from the opened path.  */
  if (found_file < 0 && solib_search_path != NULL)
    found_file = openp (solib_search_path, 
                        1, lbasename (in_pathname), O_RDONLY, 0,
                        &temp_pathname);

  /* If not found, try to use target supplied solib search method */
  if (found_file < 0 && TARGET_SO_FIND_AND_OPEN_SOLIB != NULL)
    found_file = TARGET_SO_FIND_AND_OPEN_SOLIB
                 (in_pathname, O_RDONLY, &temp_pathname);

  /* If not found, next search the inferior's $PATH environment variable. */
  if (found_file < 0 && solib_absolute_prefix == NULL)
    found_file = openp (get_in_environ (inferior_environ, "PATH"),
			1, in_pathname, O_RDONLY, 0, &temp_pathname);

  /* If not found, next search the inferior's $LD_LIBRARY_PATH 
     environment variable. */
  if (found_file < 0 && solib_absolute_prefix == NULL)
    found_file = openp (get_in_environ (inferior_environ, "LD_LIBRARY_PATH"),
			1, in_pathname, O_RDONLY, 0, &temp_pathname);

  /* Done.  If not found, tough luck.  Return found_file and 
     (optionally) found_pathname.  */
  if (found_pathname != NULL && temp_pathname != NULL)
    *found_pathname = xstrdup (temp_pathname);
  return found_file;
}