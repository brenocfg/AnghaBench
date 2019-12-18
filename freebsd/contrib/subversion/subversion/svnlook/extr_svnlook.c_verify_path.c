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
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_check_path (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_path_is_url (char const*) ; 

__attribute__((used)) static svn_error_t *
verify_path(svn_node_kind_t *kind,
            svn_fs_root_t *root,
            const char *path,
            apr_pool_t *pool)
{
  SVN_ERR(svn_fs_check_path(kind, root, path, pool));

  if (*kind == svn_node_none)
    {
      if (svn_path_is_url(path))  /* check for a common mistake. */
        return svn_error_createf
          (SVN_ERR_FS_NOT_FOUND, NULL,
           _("'%s' is a URL, probably should be a path"), path);
      else
        return svn_error_createf
          (SVN_ERR_FS_NOT_FOUND, NULL, _("Path '%s' does not exist"), path);
    }

  return SVN_NO_ERROR;
}