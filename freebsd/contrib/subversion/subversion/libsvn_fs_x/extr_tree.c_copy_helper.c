#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_18__ {TYPE_7__* parent; int /*<<< orphan*/  entry; int /*<<< orphan*/ * node; } ;
typedef  TYPE_1__ svn_fs_x__dag_path_t ;
struct TYPE_19__ {int txn_flags; int /*<<< orphan*/  rev; TYPE_3__* fs; scalar_t__ is_txn_root; } ;
typedef  TYPE_2__ svn_fs_root_t ;
typedef  scalar_t__ svn_fs_path_change_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;
struct TYPE_21__ {int /*<<< orphan*/  node; } ;
struct TYPE_20__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_change (TYPE_3__*,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  increment_mergeinfo_up_tree (TYPE_7__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_path_path (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_path_change_add ; 
 scalar_t__ svn_fs_path_change_replace ; 
 int /*<<< orphan*/  svn_fs_x__allow_locked_operation (char const*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_get_id (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__dag_get_mergeinfo_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_node_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__dag_path_last_optional ; 
 int /*<<< orphan*/  svn_fs_x__get_dag_node (int /*<<< orphan*/ **,TYPE_2__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_dag_path (TYPE_1__**,TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__id_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__invalidate_dag_cache (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__make_path_mutable (TYPE_2__*,TYPE_7__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__root_txn_id (TYPE_2__*) ; 
 int /*<<< orphan*/  x_same_p (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
copy_helper(svn_fs_root_t *from_root,
            const char *from_path,
            svn_fs_root_t *to_root,
            const char *to_path,
            svn_boolean_t preserve_history,
            apr_pool_t *scratch_pool)
{
  dag_node_t *from_node;
  svn_fs_x__dag_path_t *to_dag_path;
  svn_fs_x__txn_id_t txn_id = svn_fs_x__root_txn_id(to_root);
  svn_boolean_t same_p;

  /* Use an error check, not an assert, because even the caller cannot
     guarantee that a filesystem's UUID has not changed "on the fly". */
  SVN_ERR(x_same_p(&same_p, from_root->fs, to_root->fs, scratch_pool));
  if (! same_p)
    return svn_error_createf
      (SVN_ERR_UNSUPPORTED_FEATURE, NULL,
       _("Cannot copy between two different filesystems ('%s' and '%s')"),
       from_root->fs->path, to_root->fs->path);

  /* more things that we can't do ATM */
  if (from_root->is_txn_root)
    return svn_error_create
      (SVN_ERR_UNSUPPORTED_FEATURE, NULL,
       _("Copy from mutable tree not currently supported"));

  if (! to_root->is_txn_root)
    return svn_error_create
      (SVN_ERR_UNSUPPORTED_FEATURE, NULL,
       _("Copy immutable tree not supported"));

  /* Get the NODE for FROM_PATH in FROM_ROOT.*/
  SVN_ERR(svn_fs_x__get_dag_node(&from_node, from_root, from_path,
                                 scratch_pool, scratch_pool));

  /* Build up the parent path from TO_PATH in TO_ROOT.  If the last
     component does not exist, it's not that big a deal.  We'll just
     make one there. */
  SVN_ERR(svn_fs_x__get_dag_path(&to_dag_path, to_root, to_path,
                                 svn_fs_x__dag_path_last_optional, TRUE,
                                 scratch_pool, scratch_pool));

  /* Check to see if path (or any child thereof) is locked; if so,
     check that we can use the existing lock(s). */
  if (to_root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    SVN_ERR(svn_fs_x__allow_locked_operation(to_path, to_root->fs,
                                             TRUE, FALSE, scratch_pool));

  /* If the destination node already exists as the same node as the
     source (in other words, this operation would result in nothing
     happening at all), just do nothing an return successfully,
     proud that you saved yourself from a tiresome task. */
  if (to_dag_path->node &&
      svn_fs_x__id_eq(svn_fs_x__dag_get_id(from_node),
                      svn_fs_x__dag_get_id(to_dag_path->node)))
    return SVN_NO_ERROR;

  if (! from_root->is_txn_root)
    {
      svn_fs_path_change_kind_t kind;
      dag_node_t *new_node;
      const char *from_canonpath;
      apr_int64_t mergeinfo_start;
      apr_int64_t mergeinfo_end;

      /* If TO_PATH already existed prior to the copy, note that this
         operation is a replacement, not an addition. */
      if (to_dag_path->node)
        {
          kind = svn_fs_path_change_replace;
          mergeinfo_start
            = svn_fs_x__dag_get_mergeinfo_count(to_dag_path->node);
        }
      else
        {
          kind = svn_fs_path_change_add;
          mergeinfo_start = 0;
        }

      mergeinfo_end = svn_fs_x__dag_get_mergeinfo_count(from_node);

      /* Make sure the target node's parents are mutable.  */
      SVN_ERR(svn_fs_x__make_path_mutable(to_root, to_dag_path->parent,
                                          to_path, scratch_pool,
                                          scratch_pool));

      /* Canonicalize the copyfrom path. */
      from_canonpath = svn_fs__canonicalize_abspath(from_path, scratch_pool);

      SVN_ERR(svn_fs_x__dag_copy(to_dag_path->parent->node,
                                 to_dag_path->entry,
                                 from_node,
                                 preserve_history,
                                 from_root->rev,
                                 from_canonpath,
                                 txn_id, scratch_pool));

      if (kind != svn_fs_path_change_add)
        svn_fs_x__invalidate_dag_cache(to_root,
                                       parent_path_path(to_dag_path,
                                                        scratch_pool));

      if (mergeinfo_start != mergeinfo_end)
        SVN_ERR(increment_mergeinfo_up_tree(to_dag_path->parent,
                                            mergeinfo_end - mergeinfo_start,
                                            scratch_pool));

      /* Make a record of this modification in the changes table. */
      SVN_ERR(svn_fs_x__get_dag_node(&new_node, to_root, to_path,
                                     scratch_pool, scratch_pool));
      SVN_ERR(add_change(to_root->fs, txn_id, to_path, kind, FALSE,
                         FALSE, FALSE, svn_fs_x__dag_node_kind(from_node),
                         from_root->rev, from_canonpath, scratch_pool));
    }
  else
    {
      /* See IZ Issue #436 */
      /* Copying from transaction roots not currently available.

         ### cmpilato todo someday: make this not so. :-) Note that
         when copying from mutable trees, you have to make sure that
         you aren't creating a cyclic graph filesystem, and a simple
         referencing operation won't cut it.  Currently, we should not
         be able to reach this clause, and the interface reports that
         this only works from immutable trees anyway, but JimB has
         stated that this requirement need not be necessary in the
         future. */

      SVN_ERR_MALFUNCTION();
    }

  return SVN_NO_ERROR;
}