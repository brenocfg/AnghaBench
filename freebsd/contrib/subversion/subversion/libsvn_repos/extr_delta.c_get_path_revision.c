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
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_is_revision_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_node_created_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root_revision (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_revnum_t
get_path_revision(svn_fs_root_t *root,
                  const char *path,
                  apr_pool_t *pool)
{
  svn_revnum_t revision;
  svn_error_t *err;

  /* Easy out -- if ROOT is a revision root, we can use the revision
     that it's a root of. */
  if (svn_fs_is_revision_root(root))
    return svn_fs_revision_root_revision(root);

  /* Else, this must be a transaction root, so ask the filesystem in
     what revision this path was created. */
  if ((err = svn_fs_node_created_rev(&revision, root, path, pool)))
    {
      revision = SVN_INVALID_REVNUM;
      svn_error_clear(err);
    }

  /* If we don't get back a valid revision, this path is mutable in
     the transaction.  We should probably examine the node on which it
     is based, doable by querying for the node-id of the path, and
     then examining that node-id's predecessor.  ### This predecessor
     determination isn't exposed via the FS public API right now, so
     for now, we'll just return the SVN_INVALID_REVNUM. */
  return revision;
}