#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_9__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {int /*<<< orphan*/ * node; } ;
typedef  TYPE_2__ parent_path_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  find_youngest_copyroot (scalar_t__*,char const**,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_path (TYPE_2__**,TYPE_1__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int open_path_allow_null ; 
 int open_path_node_only ; 
 char* svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_predecessor_id (int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_revision (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__id_check_related (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__revision_root (TYPE_1__**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *fs_closest_copy(svn_fs_root_t **root_p,
                                    const char **path_p,
                                    svn_fs_root_t *root,
                                    const char *path,
                                    apr_pool_t *pool)
{
  svn_fs_t *fs = root->fs;
  parent_path_t *parent_path, *copy_dst_parent_path;
  svn_revnum_t copy_dst_rev, created_rev;
  const char *copy_dst_path;
  svn_fs_root_t *copy_dst_root;
  dag_node_t *copy_dst_node;

  /* Initialize return values. */
  *root_p = NULL;
  *path_p = NULL;

  path = svn_fs__canonicalize_abspath(path, pool);
  SVN_ERR(open_path(&parent_path, root, path, 0, FALSE, pool));

  /* Find the youngest copyroot in the path of this node-rev, which
     will indicate the target of the innermost copy affecting the
     node-rev. */
  SVN_ERR(find_youngest_copyroot(&copy_dst_rev, &copy_dst_path,
                                 fs, parent_path, pool));
  if (copy_dst_rev == 0)  /* There are no copies affecting this node-rev. */
    return SVN_NO_ERROR;

  /* It is possible that this node was created from scratch at some
     revision between COPY_DST_REV and REV.  Make sure that PATH
     exists as of COPY_DST_REV and is related to this node-rev. */
  SVN_ERR(svn_fs_fs__revision_root(&copy_dst_root, fs, copy_dst_rev, pool));
  SVN_ERR(open_path(&copy_dst_parent_path, copy_dst_root, path,
                    open_path_node_only | open_path_allow_null, FALSE, pool));
  if (copy_dst_parent_path == NULL)
    return SVN_NO_ERROR;

  copy_dst_node = copy_dst_parent_path->node;
  if (! svn_fs_fs__id_check_related(svn_fs_fs__dag_get_id(copy_dst_node),
                                    svn_fs_fs__dag_get_id(parent_path->node)))
    return SVN_NO_ERROR;

  /* One final check must be done here.  If you copy a directory and
     create a new entity somewhere beneath that directory in the same
     txn, then we can't claim that the copy affected the new entity.
     For example, if you do:

        copy dir1 dir2
        create dir2/new-thing
        commit

     then dir2/new-thing was not affected by the copy of dir1 to dir2.
     We detect this situation by asking if PATH@COPY_DST_REV's
     created-rev is COPY_DST_REV, and that node-revision has no
     predecessors, then there is no relevant closest copy.
  */
  SVN_ERR(svn_fs_fs__dag_get_revision(&created_rev, copy_dst_node, pool));
  if (created_rev == copy_dst_rev)
    {
      const svn_fs_id_t *pred;
      SVN_ERR(svn_fs_fs__dag_get_predecessor_id(&pred, copy_dst_node));
      if (! pred)
        return SVN_NO_ERROR;
    }

  /* The copy destination checks out.  Return it. */
  *root_p = copy_dst_root;
  *path_p = copy_dst_path;
  return SVN_NO_ERROR;
}