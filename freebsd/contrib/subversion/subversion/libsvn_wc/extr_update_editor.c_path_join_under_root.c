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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_OBSTRUCTED_UPDATE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_under_root (int /*<<< orphan*/ *,char const**,char const*,char const*,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static svn_error_t *
path_join_under_root(const char **result_path,
                     const char *base_path,
                     const char *add_path,
                     apr_pool_t *pool)
{
  svn_boolean_t under_root;

  SVN_ERR(svn_dirent_is_under_root(&under_root,
                                   result_path, base_path, add_path, pool));

  if (! under_root)
    {
      return svn_error_createf(
          SVN_ERR_WC_OBSTRUCTED_UPDATE, NULL,
          _("Path '%s' is not in the working copy"),
          svn_dirent_local_style(svn_dirent_join(base_path, add_path, pool),
                                 pool));
    }

  /* This catches issue #3288 */
  if (strcmp(add_path, svn_dirent_basename(*result_path, NULL)) != 0)
    {
      return svn_error_createf(
          SVN_ERR_WC_OBSTRUCTED_UPDATE, NULL,
          _("'%s' is not valid as filename in directory '%s'"),
          svn_dirent_local_style(add_path, pool),
          svn_dirent_local_style(base_path, pool));
    }

  return SVN_NO_ERROR;
}