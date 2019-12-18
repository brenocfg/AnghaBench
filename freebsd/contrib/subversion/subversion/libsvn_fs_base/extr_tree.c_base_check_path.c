#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_ERR_FS_NOT_DIRECTORY ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 TYPE_1__* node_kind (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_node_none ; 

__attribute__((used)) static svn_error_t *
base_check_path(svn_node_kind_t *kind_p,
                svn_fs_root_t *root,
                const char *path,
                apr_pool_t *pool)
{
  svn_error_t *err = node_kind(kind_p, root, path, pool);
  if (err &&
      ((err->apr_err == SVN_ERR_FS_NOT_FOUND)
       || (err->apr_err == SVN_ERR_FS_NOT_DIRECTORY)))
    {
      svn_error_clear(err);
      err = SVN_NO_ERROR;
      *kind_p = svn_node_none;
    }

  return svn_error_trace(err);
}