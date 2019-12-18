#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  pool; TYPE_1__* fs; } ;
typedef  TYPE_2__ trail_t ;
struct TYPE_24__ {char* txn; int txn_flags; int /*<<< orphan*/  fs; int /*<<< orphan*/  rev; int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_3__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_path_change_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct copy_args {char* from_path; char* to_path; int /*<<< orphan*/  preserve_history; TYPE_3__* to_root; TYPE_3__* from_root; } ;
struct TYPE_25__ {TYPE_14__* parent; int /*<<< orphan*/  entry; int /*<<< orphan*/ * node; } ;
typedef  TYPE_4__ parent_path_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_26__ {scalar_t__ format; } ;
typedef  TYPE_5__ base_fs_data_t ;
typedef  scalar_t__ apr_int64_t ;
struct TYPE_22__ {TYPE_5__* fsap_data; } ;
struct TYPE_21__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 scalar_t__ SVN_FS_BASE__MIN_MERGEINFO_FORMAT ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_change (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjust_parent_mergeinfo_counts (TYPE_14__*,scalar_t__,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dag (int /*<<< orphan*/ **,TYPE_3__*,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_path_mutable (TYPE_3__*,TYPE_14__*,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_path (TYPE_4__**,TYPE_3__*,char const*,int /*<<< orphan*/ ,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_path_last_optional ; 
 int /*<<< orphan*/  svn_fs_base__allow_locked_operation (char const*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_mergeinfo_stats (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_base__id_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_node_unchanged ; 
 int /*<<< orphan*/  svn_fs_path_change_add ; 
 int /*<<< orphan*/  svn_fs_path_change_replace ; 

__attribute__((used)) static svn_error_t *
txn_body_copy(void *baton,
              trail_t *trail)
{
  struct copy_args *args = baton;
  svn_fs_root_t *from_root = args->from_root;
  const char *from_path = args->from_path;
  svn_fs_root_t *to_root = args->to_root;
  const char *to_path = args->to_path;
  dag_node_t *from_node;
  parent_path_t *to_parent_path;
  const char *txn_id = to_root->txn;

  /* Get the NODE for FROM_PATH in FROM_ROOT.*/
  SVN_ERR(get_dag(&from_node, from_root, from_path, trail, trail->pool));

  /* Build up the parent path from TO_PATH in TO_ROOT.  If the last
     component does not exist, it's not that big a deal.  We'll just
     make one there. */
  SVN_ERR(open_path(&to_parent_path, to_root, to_path,
                    open_path_last_optional, txn_id, trail, trail->pool));

  /* Check to see if to-path (or any child thereof) is locked, or at
     least 'reserved', whether it exists or not; if so, check that we
     can use the existing lock(s). */
  if (to_root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    {
      SVN_ERR(svn_fs_base__allow_locked_operation(to_path, TRUE,
                                                  trail, trail->pool));
    }

  /* If the destination node already exists as the same node as the
     source (in other words, this operation would result in nothing
     happening at all), just do nothing an return successfully,
     proud that you saved yourself from a tiresome task. */
  if ((to_parent_path->node)
      && (svn_fs_base__id_compare(svn_fs_base__dag_get_id(from_node),
                                  svn_fs_base__dag_get_id
                                  (to_parent_path->node))
          == svn_fs_node_unchanged))
    return SVN_NO_ERROR;

  if (! from_root->is_txn_root)
    {
      svn_fs_path_change_kind_t kind;
      dag_node_t *new_node;
      apr_int64_t old_mergeinfo_count = 0, mergeinfo_count;
      base_fs_data_t *bfd = trail->fs->fsap_data;

      /* If TO_PATH already existed prior to the copy, note that this
         operation is a replacement, not an addition. */
      if (to_parent_path->node)
        kind = svn_fs_path_change_replace;
      else
        kind = svn_fs_path_change_add;

      /* Make sure the target node's parents are mutable.  */
      SVN_ERR(make_path_mutable(to_root, to_parent_path->parent,
                                to_path, trail, trail->pool));

      /* If this is a replacement operation, we need to know the old
         node's mergeinfo count. */
      if (to_parent_path->node)
        SVN_ERR(svn_fs_base__dag_get_mergeinfo_stats(NULL,
                                                     &old_mergeinfo_count,
                                                     to_parent_path->node,
                                                     trail, trail->pool));
      /* Do the copy. */
      SVN_ERR(svn_fs_base__dag_copy(to_parent_path->parent->node,
                                    to_parent_path->entry,
                                    from_node,
                                    args->preserve_history,
                                    from_root->rev,
                                    from_path, txn_id, trail, trail->pool));

      /* Adjust the mergeinfo counts of the destination's parents if
         our format supports it. */
      if (bfd->format >= SVN_FS_BASE__MIN_MERGEINFO_FORMAT)
        {
          SVN_ERR(svn_fs_base__dag_get_mergeinfo_stats(NULL,
                                                       &mergeinfo_count,
                                                       from_node, trail,
                                                       trail->pool));
          SVN_ERR(adjust_parent_mergeinfo_counts
                  (to_parent_path->parent,
                   mergeinfo_count - old_mergeinfo_count,
                   txn_id, trail, trail->pool));
        }

      /* Make a record of this modification in the changes table. */
      SVN_ERR(get_dag(&new_node, to_root, to_path, trail, trail->pool));
      SVN_ERR(add_change(to_root->fs, txn_id, to_path,
                         svn_fs_base__dag_get_id(new_node),
                         kind, FALSE, FALSE, trail, trail->pool));
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