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
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int strlen (char const*) ; 
 scalar_t__ svn_dirent_is_canonical (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_dirent_is_root (char const*,int) ; 

const char *
svn_dirent_basename(const char *dirent, apr_pool_t *pool)
{
  apr_size_t len = strlen(dirent);
  apr_size_t start;

  assert(!pool || svn_dirent_is_canonical(dirent, pool));

  if (svn_dirent_is_root(dirent, len))
    return "";
  else
    {
      start = len;
      while (start > 0 && dirent[start - 1] != '/'
#ifdef SVN_USE_DOS_PATHS
             && dirent[start - 1] != ':'
#endif
            )
        --start;
    }

  if (pool)
    return apr_pstrmemdup(pool, dirent + start, len - start);
  else
    return dirent + start;
}