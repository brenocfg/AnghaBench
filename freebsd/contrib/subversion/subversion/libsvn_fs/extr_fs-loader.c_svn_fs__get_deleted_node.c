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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_closest_copy (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_copied_from (scalar_t__*,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_revision_root_revision (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_root_fs (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_txn_root_base_revision (int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_fspath__split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs__get_deleted_node(svn_fs_root_t **node_root,
                         const char **node_path,
                         svn_fs_root_t *root,
                         const char *path,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  const char *parent_path, *name;
  svn_fs_root_t *copy_root;
  const char *copy_path;

  /* History traversal does not work with transaction roots.
   * Therefore, do it "by hand". */

  /* If the parent got copied in ROOT, PATH got copied with it.
   * Otherwise, we will find the node at PATH in the revision prior to ROOT.
   */
  svn_fspath__split(&parent_path, &name, path, scratch_pool);
  SVN_ERR(svn_fs_closest_copy(&copy_root, &copy_path, root, parent_path,
                              scratch_pool));

  /* Copied in ROOT? */
  if (   copy_root
      && (   svn_fs_revision_root_revision(copy_root)
          == svn_fs_revision_root_revision(root)))
    {
      svn_revnum_t copyfrom_rev;
      const char *copyfrom_path;
      const char *rel_path;
      SVN_ERR(svn_fs_copied_from(&copyfrom_rev, &copyfrom_path,
                                 copy_root, copy_path, scratch_pool));

      SVN_ERR(svn_fs_revision_root(node_root, svn_fs_root_fs(root),
                                   copyfrom_rev, result_pool));
      rel_path = svn_fspath__skip_ancestor(copy_path, path);
      *node_path = svn_fspath__join(copyfrom_path, rel_path, result_pool);
    }
  else
    {
      svn_revnum_t revision;
      svn_revnum_t previous_rev;

      /* Determine the latest revision before ROOT. */
      revision = svn_fs_revision_root_revision(root);
      if (SVN_IS_VALID_REVNUM(revision))
        previous_rev = revision - 1;
      else
        previous_rev = svn_fs_txn_root_base_revision(root);

      SVN_ERR(svn_fs_revision_root(node_root, svn_fs_root_fs(root),
                                   previous_rev, result_pool));
      *node_path = apr_pstrdup(result_pool, path);
    }

  return SVN_NO_ERROR;
}