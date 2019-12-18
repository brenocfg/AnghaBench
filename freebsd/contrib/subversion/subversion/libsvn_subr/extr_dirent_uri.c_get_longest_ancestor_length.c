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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  scalar_t__ path_type_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_PATH_IS_EMPTY (char const*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t strlen (char const*) ; 
 scalar_t__ type_dirent ; 

__attribute__((used)) static apr_size_t
get_longest_ancestor_length(path_type_t types,
                            const char *path1,
                            const char *path2,
                            apr_pool_t *pool)
{
  apr_size_t path1_len, path2_len;
  apr_size_t i = 0;
  apr_size_t last_dirsep = 0;
#ifdef SVN_USE_DOS_PATHS
  svn_boolean_t unc = FALSE;
#endif

  path1_len = strlen(path1);
  path2_len = strlen(path2);

  if (SVN_PATH_IS_EMPTY(path1) || SVN_PATH_IS_EMPTY(path2))
    return 0;

  while (path1[i] == path2[i])
    {
      /* Keep track of the last directory separator we hit. */
      if (path1[i] == '/')
        last_dirsep = i;

      i++;

      /* If we get to the end of either path, break out. */
      if ((i == path1_len) || (i == path2_len))
        break;
    }

  /* two special cases:
     1. '/' is the longest common ancestor of '/' and '/foo' */
  if (i == 1 && path1[0] == '/' && path2[0] == '/')
    return 1;
  /* 2. '' is the longest common ancestor of any non-matching
   * strings 'foo' and 'bar' */
  if (types == type_dirent && i == 0)
    return 0;

  /* Handle some windows specific cases */
#ifdef SVN_USE_DOS_PATHS
  if (types == type_dirent)
    {
      /* don't count the '//' from UNC paths */
      if (last_dirsep == 1 && path1[0] == '/' && path1[1] == '/')
        {
          last_dirsep = 0;
          unc = TRUE;
        }

      /* X:/ and X:/foo */
      if (i == 3 && path1[2] == '/' && path1[1] == ':')
        return i;

      /* Cannot use SVN_ERR_ASSERT here, so we'll have to crash, sorry.
       * Note that this assertion triggers only if the code above has
       * been broken. The code below relies on this assertion, because
       * it uses [i - 1] as index. */
      assert(i > 0);

      /* X: and X:/ */
      if ((path1[i - 1] == ':' && path2[i] == '/') ||
          (path2[i - 1] == ':' && path1[i] == '/'))
          return 0;
      /* X: and X:foo */
      if (path1[i - 1] == ':' || path2[i - 1] == ':')
          return i;
    }
#endif /* SVN_USE_DOS_PATHS */

  /* last_dirsep is now the offset of the last directory separator we
     crossed before reaching a non-matching byte.  i is the offset of
     that non-matching byte, and is guaranteed to be <= the length of
     whichever path is shorter.
     If one of the paths is the common part return that. */
  if (((i == path1_len) && (path2[i] == '/'))
           || ((i == path2_len) && (path1[i] == '/'))
           || ((i == path1_len) && (i == path2_len)))
    return i;
  else
    {
      /* Nothing in common but the root folder '/' or 'X:/' for Windows
         dirents. */
#ifdef SVN_USE_DOS_PATHS
      if (! unc)
        {
          /* X:/foo and X:/bar returns X:/ */
          if ((types == type_dirent) &&
              last_dirsep == 2 && path1[1] == ':' && path1[2] == '/'
                               && path2[1] == ':' && path2[2] == '/')
            return 3;
#endif /* SVN_USE_DOS_PATHS */
          if (last_dirsep == 0 && path1[0] == '/' && path2[0] == '/')
            return 1;
#ifdef SVN_USE_DOS_PATHS
        }
#endif
    }

  return last_dirsep;
}