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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int) ; 
 char* strrchr (char const*,char) ; 

void
svn_path_splitext(const char **path_root,
                  const char **path_ext,
                  const char *path,
                  apr_pool_t *pool)
{
  const char *last_dot, *last_slash;

  /* Easy out -- why do all the work when there's no way to report it? */
  if (! (path_root || path_ext))
    return;

  /* Do we even have a period in this thing?  And if so, is there
     anything after it?  We look for the "rightmost" period in the
     string. */
  last_dot = strrchr(path, '.');
  if (last_dot && (*(last_dot + 1) != '\0'))
    {
      /* If we have a period, we need to make sure it occurs in the
         final path component -- that there's no path separator
         between the last period and the end of the PATH -- otherwise,
         it doesn't count.  Also, we want to make sure that our period
         isn't the first character of the last component. */
      last_slash = strrchr(path, '/');
      if ((last_slash && (last_dot > (last_slash + 1)))
          || ((! last_slash) && (last_dot > path)))
        {
          if (path_root)
            *path_root = apr_pstrmemdup(pool, path,
                                        (last_dot - path + 1) * sizeof(*path));
          if (path_ext)
            *path_ext = apr_pstrdup(pool, last_dot + 1);
          return;
        }
    }
  /* If we get here, we never found a suitable separator character, so
     there's no split. */
  if (path_root)
    *path_root = apr_pstrdup(pool, path);
  if (path_ext)
    *path_ext = "";
}