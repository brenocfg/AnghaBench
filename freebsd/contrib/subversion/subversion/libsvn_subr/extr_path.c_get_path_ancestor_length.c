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
 size_t strlen (char const*) ; 

__attribute__((used)) static apr_size_t
get_path_ancestor_length(const char *path1,
                         const char *path2,
                         apr_pool_t *pool)
{
  apr_size_t path1_len, path2_len;
  apr_size_t i = 0;
  apr_size_t last_dirsep = 0;

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
     1. '/' is the longest common ancestor of '/' and '/foo'
     2. '/' is the longest common ancestor of '/rif' and '/raf' */
  if (i == 1 && path1[0] == '/' && path2[0] == '/')
    return 1;

  /* last_dirsep is now the offset of the last directory separator we
     crossed before reaching a non-matching byte.  i is the offset of
     that non-matching byte. */
  if (((i == path1_len) && (path2[i] == '/'))
           || ((i == path2_len) && (path1[i] == '/'))
           || ((i == path1_len) && (i == path2_len)))
    return i;
  else
    if (last_dirsep == 0 && path1[0] == '/' && path2[0] == '/')
      return 1;
  return last_dirsep;
}