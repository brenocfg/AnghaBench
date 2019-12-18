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
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_PATH_IS_EMPTY (char const*) ; 
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 

const char *
svn_path_is_child(const char *path1,
                  const char *path2,
                  apr_pool_t *pool)
{
  apr_size_t i;

  /* assert (is_canonical (path1, strlen (path1)));  ### Expensive strlen */
  /* assert (is_canonical (path2, strlen (path2)));  ### Expensive strlen */

  /* Allow "" and "foo" to be parent/child */
  if (SVN_PATH_IS_EMPTY(path1))               /* "" is the parent  */
    {
      if (SVN_PATH_IS_EMPTY(path2)            /* "" not a child    */
          || path2[0] == '/')                  /* "/foo" not a child */
        return NULL;
      else
        /* everything else is child */
        return pool ? apr_pstrdup(pool, path2) : path2;
    }

  /* Reach the end of at least one of the paths.  How should we handle
     things like path1:"foo///bar" and path2:"foo/bar/baz"?  It doesn't
     appear to arise in the current Subversion code, it's not clear to me
     if they should be parent/child or not. */
  for (i = 0; path1[i] && path2[i]; i++)
    if (path1[i] != path2[i])
      return NULL;

  /* There are two cases that are parent/child
          ...      path1[i] == '\0'
          .../foo  path2[i] == '/'
      or
          /        path1[i] == '\0'
          /foo     path2[i] != '/'
  */
  if (path1[i] == '\0' && path2[i])
    {
      if (path2[i] == '/')
        return pool ? apr_pstrdup(pool, path2 + i + 1) : path2 + i + 1;
      else if (i == 1 && path1[0] == '/')
        return pool ? apr_pstrdup(pool, path2 + 1) : path2 + 1;
    }

  /* Otherwise, path2 isn't a child. */
  return NULL;
}