#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct merge_args {int /*<<< orphan*/  conflict; int /*<<< orphan*/ * ancestor_node; int /*<<< orphan*/ * source_node; TYPE_1__* txn; } ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_11__ {char* id; int /*<<< orphan*/ * fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  merge (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_predecessor_count (int*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_txn_base_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_txn_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_base__id_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__set_txn_base (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__set_txn_root (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_ancestry (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char const*,char*,int,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_merge(void *baton, trail_t *trail)
{
  struct merge_args *args = baton;
  dag_node_t *source_node, *txn_root_node, *ancestor_node;
  const svn_fs_id_t *source_id;
  svn_fs_t *fs = args->txn->fs;
  const char *txn_id = args->txn->id;

  source_node = args->source_node;
  ancestor_node = args->ancestor_node;
  source_id = svn_fs_base__dag_get_id(source_node);

  SVN_ERR(svn_fs_base__dag_txn_root(&txn_root_node, fs, txn_id,
                                    trail, trail->pool));

  if (ancestor_node == NULL)
    {
      SVN_ERR(svn_fs_base__dag_txn_base_root(&ancestor_node, fs,
                                             txn_id, trail, trail->pool));
    }

  if (svn_fs_base__id_eq(svn_fs_base__dag_get_id(ancestor_node),
                         svn_fs_base__dag_get_id(txn_root_node)))
    {
      /* If no changes have been made in TXN since its current base,
         then it can't conflict with any changes since that base.  So
         we just set *both* its base and root to source, making TXN
         in effect a repeat of source. */

      /* ### kff todo: this would, of course, be a mighty silly thing
         for the caller to do, and we might want to consider whether
         this response is really appropriate. */

      SVN_ERR(svn_fs_base__set_txn_base(fs, txn_id, source_id,
                                        trail, trail->pool));
      SVN_ERR(svn_fs_base__set_txn_root(fs, txn_id, source_id,
                                        trail, trail->pool));
    }
  else
    {
      int pred_count;

      SVN_ERR(merge(args->conflict, "/", txn_root_node, source_node,
                    ancestor_node, txn_id, NULL, trail, trail->pool));

      SVN_ERR(svn_fs_base__dag_get_predecessor_count(&pred_count,
                                                     source_node, trail,
                                                     trail->pool));

      /* After the merge, txn's new "ancestor" is now really the node
         at source_id, so record that fact.  Think of this as
         ratcheting the txn forward in time, so it can't backslide and
         forget the merging work that's already been done. */
      SVN_ERR(update_ancestry(fs, source_id,
                              svn_fs_base__dag_get_id(txn_root_node),
                              txn_id, "/", pred_count, trail, trail->pool));
      SVN_ERR(svn_fs_base__set_txn_base(fs, txn_id, source_id,
                                        trail, trail->pool));
    }

  return SVN_NO_ERROR;
}