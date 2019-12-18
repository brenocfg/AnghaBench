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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ check_repos_path (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_dirent_is_root (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_path_cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_empty (char const*) ; 

const char *
svn_repos_find_root_path(const char *path,
                         apr_pool_t *pool)
{
  const char *candidate = path;
  const char *decoded;
  svn_error_t *err;

  while (1)
    {
      /* Try to decode the path, so we don't fail if it contains characters
         that aren't supported by the OS filesystem.  The subversion fs
         isn't restricted by the OS filesystem character set. */
      err = svn_path_cstring_from_utf8(&decoded, candidate, pool);
      if (!err && check_repos_path(candidate, pool))
        break;
      svn_error_clear(err);

      if (svn_path_is_empty(candidate) ||
          svn_dirent_is_root(candidate, strlen(candidate)))
        return NULL;

      candidate = svn_dirent_dirname(candidate, pool);
    }

  return candidate;
}