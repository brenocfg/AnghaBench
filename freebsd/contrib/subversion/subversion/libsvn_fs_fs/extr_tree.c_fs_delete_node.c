#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_node_kind_t ;
struct TYPE_13__ {int txn_flags; int /*<<< orphan*/  fs; int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_14__ {int /*<<< orphan*/  node; TYPE_8__* parent; int /*<<< orphan*/  entry; } ;
typedef  TYPE_2__ parent_path_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
struct TYPE_15__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_ROOT_DIR ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/ * SVN_FS__NOT_TXN (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * add_change (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dag_node_cache_invalidate (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  increment_mergeinfo_up_tree (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_path_mutable (TYPE_1__*,TYPE_8__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_path (TYPE_2__**,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_path_path (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * root_txn_id (TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__allow_locked_operation (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_mergeinfo_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_node_kind (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_fs__fs_supports_mergeinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_path_change_delete ; 

__attribute__((used)) static svn_error_t *
fs_delete_node(svn_fs_root_t *root,
               const char *path,
               apr_pool_t *pool)
{
  parent_path_t *parent_path;
  const svn_fs_fs__id_part_t *txn_id;
  apr_int64_t mergeinfo_count = 0;
  svn_node_kind_t kind;

  if (! root->is_txn_root)
    return SVN_FS__NOT_TXN(root);

  txn_id = root_txn_id(root);
  path = svn_fs__canonicalize_abspath(path, pool);
  SVN_ERR(open_path(&parent_path, root, path, 0, TRUE, pool));
  kind = svn_fs_fs__dag_node_kind(parent_path->node);

  /* We can't remove the root of the filesystem.  */
  if (! parent_path->parent)
    return svn_error_create(SVN_ERR_FS_ROOT_DIR, NULL,
                            _("The root directory cannot be deleted"));

  /* Check to see if path (or any child thereof) is locked; if so,
     check that we can use the existing lock(s). */
  if (root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    SVN_ERR(svn_fs_fs__allow_locked_operation(path, root->fs, TRUE, FALSE,
                                              pool));

  /* Make the parent directory mutable, and do the deletion.  */
  SVN_ERR(make_path_mutable(root, parent_path->parent, path, pool));
  if (svn_fs_fs__fs_supports_mergeinfo(root->fs))
    SVN_ERR(svn_fs_fs__dag_get_mergeinfo_count(&mergeinfo_count,
                                               parent_path->node));
  SVN_ERR(svn_fs_fs__dag_delete(parent_path->parent->node,
                                parent_path->entry,
                                txn_id, pool));

  /* Remove this node and any children from the path cache. */
  SVN_ERR(dag_node_cache_invalidate(root, parent_path_path(parent_path, pool),
                                    pool));

  /* Update mergeinfo counts for parents */
  if (mergeinfo_count > 0)
    SVN_ERR(increment_mergeinfo_up_tree(parent_path->parent,
                                        -mergeinfo_count,
                                        pool));

  /* Make a record of this modification in the changes table. */
  return add_change(root->fs, txn_id, path,
                    svn_fs_fs__dag_get_id(parent_path->node),
                    svn_fs_path_change_delete, FALSE, FALSE, FALSE, kind,
                    SVN_INVALID_REVNUM, NULL, pool);
}