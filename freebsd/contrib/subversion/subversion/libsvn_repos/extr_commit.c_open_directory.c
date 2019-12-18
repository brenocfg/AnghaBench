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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {int /*<<< orphan*/  txn_root; int /*<<< orphan*/  base_path; } ;
struct dir_baton {int /*<<< orphan*/  was_copied; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_DIRECTORY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* make_dir_baton (struct edit_baton*,struct dir_baton*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_check_path (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_directory(const char *path,
               void *parent_baton,
               svn_revnum_t base_revision,
               apr_pool_t *pool,
               void **child_baton)
{
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;
  svn_node_kind_t kind;
  const char *full_path;

  full_path = svn_fspath__join(eb->base_path,
                               svn_relpath_canonicalize(path, pool), pool);

  /* Check PATH in our transaction.  If it does not exist,
     return a 'Path not present' error. */
  SVN_ERR(svn_fs_check_path(&kind, eb->txn_root, full_path, pool));
  if (kind == svn_node_none)
    return svn_error_createf(SVN_ERR_FS_NOT_DIRECTORY, NULL,
                             _("Path '%s' not present"),
                             path);

  /* Build a new dir baton for this directory. */
  *child_baton = make_dir_baton(eb, pb, full_path, pb->was_copied,
                                base_revision, pool);
  return SVN_NO_ERROR;
}