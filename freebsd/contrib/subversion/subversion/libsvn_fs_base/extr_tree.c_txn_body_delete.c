#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  pool; TYPE_1__* fs; } ;
typedef  TYPE_2__ trail_t ;
struct TYPE_23__ {char* txn; int txn_flags; int /*<<< orphan*/  fs; int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_3__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct delete_args {char* path; TYPE_3__* root; } ;
struct TYPE_24__ {int /*<<< orphan*/  node; int /*<<< orphan*/  entry; TYPE_14__* parent; } ;
typedef  TYPE_4__ parent_path_t ;
struct TYPE_25__ {scalar_t__ format; } ;
typedef  TYPE_5__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
struct TYPE_21__ {TYPE_5__* fsap_data; } ;
struct TYPE_20__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_ROOT_DIR ; 
 scalar_t__ SVN_FS_BASE__MIN_MERGEINFO_FORMAT ; 
 int SVN_FS_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/ * SVN_FS__NOT_TXN (TYPE_3__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * add_change (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjust_parent_mergeinfo_counts (TYPE_14__*,int /*<<< orphan*/ ,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_path_mutable (TYPE_3__*,TYPE_14__*,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_path (TYPE_4__**,TYPE_3__*,char const*,int /*<<< orphan*/ ,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__allow_locked_operation (char const*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_mergeinfo_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_path_change_delete ; 

__attribute__((used)) static svn_error_t *
txn_body_delete(void *baton,
                trail_t *trail)
{
  struct delete_args *args = baton;
  svn_fs_root_t *root = args->root;
  const char *path = args->path;
  parent_path_t *parent_path;
  const char *txn_id = root->txn;
  base_fs_data_t *bfd = trail->fs->fsap_data;

  if (! root->is_txn_root)
    return SVN_FS__NOT_TXN(root);

  SVN_ERR(open_path(&parent_path, root, path, 0, txn_id,
                    trail, trail->pool));

  /* We can't remove the root of the filesystem.  */
  if (! parent_path->parent)
    return svn_error_create(SVN_ERR_FS_ROOT_DIR, NULL,
                            _("The root directory cannot be deleted"));

  /* Check to see if path (or any child thereof) is locked; if so,
     check that we can use the existing lock(s). */
  if (root->txn_flags & SVN_FS_TXN_CHECK_LOCKS)
    {
      SVN_ERR(svn_fs_base__allow_locked_operation(path, TRUE,
                                                  trail, trail->pool));
    }

  /* Make the parent directory mutable. */
  SVN_ERR(make_path_mutable(root, parent_path->parent, path,
                            trail, trail->pool));

  /* Decrement mergeinfo counts on the parents of this node by the
     count it previously carried, if our format supports it. */
  if (bfd->format >= SVN_FS_BASE__MIN_MERGEINFO_FORMAT)
    {
      apr_int64_t mergeinfo_count;
      SVN_ERR(svn_fs_base__dag_get_mergeinfo_stats(NULL, &mergeinfo_count,
                                                   parent_path->node,
                                                   trail, trail->pool));
      SVN_ERR(adjust_parent_mergeinfo_counts(parent_path->parent,
                                             -mergeinfo_count, txn_id,
                                             trail, trail->pool));
    }

  /* Do the deletion. */
  SVN_ERR(svn_fs_base__dag_delete(parent_path->parent->node,
                                  parent_path->entry,
                                  txn_id, trail, trail->pool));


  /* Make a record of this modification in the changes table. */
  return add_change(root->fs, txn_id, path,
                    svn_fs_base__dag_get_id(parent_path->node),
                    svn_fs_path_change_delete, FALSE, FALSE, trail,
                    trail->pool);
}