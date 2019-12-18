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
struct TYPE_9__ {int /*<<< orphan*/ * node; } ;
typedef  TYPE_1__ svn_fs_x__dag_path_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_10__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  find_youngest_copyroot (scalar_t__*,char const**,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_predecessor_id (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__dag_get_revision (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_path_allow_null ; 
 int /*<<< orphan*/  svn_fs_x__dag_related_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_dag_path (TYPE_1__**,TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__id_used (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__revision_root (TYPE_2__**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x_closest_copy(svn_fs_root_t **root_p,
               const char **path_p,
               svn_fs_root_t *root,
               const char *path,
               apr_pool_t *pool)
{
  svn_fs_t *fs = root->fs;
  svn_fs_x__dag_path_t *dag_path, *copy_dst_dag_path;
  svn_revnum_t copy_dst_rev, created_rev;
  const char *copy_dst_path;
  svn_fs_root_t *copy_dst_root;
  dag_node_t *copy_dst_node;
  apr_pool_t *scratch_pool = svn_pool_create(pool);

  /* Initialize return values. */
  *root_p = NULL;
  *path_p = NULL;

  SVN_ERR(svn_fs_x__get_dag_path(&dag_path, root, path, 0, FALSE,
                                 scratch_pool, scratch_pool));

  /* Find the youngest copyroot in the path of this node-rev, which
     will indicate the target of the innermost copy affecting the
     node-rev. */
  SVN_ERR(find_youngest_copyroot(&copy_dst_rev, &copy_dst_path,
                                 fs, dag_path));
  if (copy_dst_rev == 0)  /* There are no copies affecting this node-rev. */
    {
      svn_pool_destroy(scratch_pool);
      return SVN_NO_ERROR;
    }

  /* It is possible that this node was created from scratch at some
     revision between COPY_DST_REV and REV.  Make sure that PATH
     exists as of COPY_DST_REV and is related to this node-rev. */
  SVN_ERR(svn_fs_x__revision_root(&copy_dst_root, fs, copy_dst_rev, pool));
  SVN_ERR(svn_fs_x__get_dag_path(&copy_dst_dag_path, copy_dst_root, path,
                                 svn_fs_x__dag_path_allow_null, FALSE,
                                 scratch_pool, scratch_pool));
  if (copy_dst_dag_path == NULL)
    {
      svn_pool_destroy(scratch_pool);
      return SVN_NO_ERROR;
    }

  copy_dst_node = copy_dst_dag_path->node;
  if (!svn_fs_x__dag_related_node(copy_dst_node, dag_path->node))
    {
      svn_pool_destroy(scratch_pool);
      return SVN_NO_ERROR;
    }

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
  created_rev = svn_fs_x__dag_get_revision(copy_dst_node);
  if (created_rev == copy_dst_rev)
    if (!svn_fs_x__id_used(svn_fs_x__dag_get_predecessor_id(copy_dst_node)))
      {
        svn_pool_destroy(scratch_pool);
        return SVN_NO_ERROR;
      }

  /* The copy destination checks out.  Return it. */
  *root_p = copy_dst_root;
  *path_p = apr_pstrdup(pool, copy_dst_path);

  svn_pool_destroy(scratch_pool);
  return SVN_NO_ERROR;
}