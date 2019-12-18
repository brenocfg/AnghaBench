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
typedef  scalar_t__ path_type_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_PATH_IS_EMPTY (char const*) ; 
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ dirent_is_rooted (char const*) ; 
 scalar_t__ type_dirent ; 
 scalar_t__ type_uri ; 

__attribute__((used)) static const char *
is_child(path_type_t type, const char *path1, const char *path2,
         apr_pool_t *pool)
{
  apr_size_t i;

  /* Allow "" and "foo" or "H:foo" to be parent/child */
  if (SVN_PATH_IS_EMPTY(path1))               /* "" is the parent  */
    {
      if (SVN_PATH_IS_EMPTY(path2))            /* "" not a child    */
        return NULL;

      /* check if this is an absolute path */
      if ((type == type_uri) ||
          (type == type_dirent && dirent_is_rooted(path2)))
        return NULL;
      else
        /* everything else is child */
        return pool ? apr_pstrdup(pool, path2) : path2;
    }

  /* Reach the end of at least one of the paths.  How should we handle
     things like path1:"foo///bar" and path2:"foo/bar/baz"?  It doesn't
     appear to arise in the current Subversion code, it's not clear to me
     if they should be parent/child or not. */
  /* Hmmm... aren't paths assumed to be canonical in this function?
   * How can "foo///bar" even happen if the paths are canonical? */
  for (i = 0; path1[i] && path2[i]; i++)
    if (path1[i] != path2[i])
      return NULL;

  /* FIXME: This comment does not really match
   * the checks made in the code it refers to: */
  /* There are two cases that are parent/child
          ...      path1[i] == '\0'
          .../foo  path2[i] == '/'
      or
          /        path1[i] == '\0'
          /foo     path2[i] != '/'

     Other root paths (like X:/) fall under the former case:
          X:/        path1[i] == '\0'
          X:/foo     path2[i] != '/'

     Check for '//' to avoid matching '/' and '//srv'.
  */
  if (path1[i] == '\0' && path2[i])
    {
      if (path1[i - 1] == '/'
#ifdef SVN_USE_DOS_PATHS
          || ((type == type_dirent) && path1[i - 1] == ':')
#endif
           )
        {
          if (path2[i] == '/')
            /* .../
             * ..../
             *     i   */
            return NULL;
          else
            /* .../
             * .../foo
             *     i    */
            return pool ? apr_pstrdup(pool, path2 + i) : path2 + i;
        }
      else if (path2[i] == '/')
        {
          if (path2[i + 1])
            /* ...
             * .../foo
             *    i    */
            return pool ? apr_pstrdup(pool, path2 + i + 1) : path2 + i + 1;
          else
            /* ...
             * .../
             *    i    */
            return NULL;
        }
    }

  /* Otherwise, path2 isn't a child. */
  return NULL;
}