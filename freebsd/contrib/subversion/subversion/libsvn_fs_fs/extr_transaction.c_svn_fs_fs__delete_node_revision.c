#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_12__ {scalar_t__ kind; scalar_t__ data_rep; scalar_t__ prop_rep; } ;
typedef  TYPE_2__ node_revision_t ;
struct TYPE_13__ {scalar_t__ txn_dir_cache; } ;
typedef  TYPE_3__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_14__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ is_txn_rep (scalar_t__) ; 
 int /*<<< orphan*/ * svn_cache__set (scalar_t__,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__get_node_revision (TYPE_2__**,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_7__* svn_fs_fs__id_unparse (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_node_children (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_node_props (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_node_rev (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_remove_file2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 

svn_error_t *
svn_fs_fs__delete_node_revision(svn_fs_t *fs,
                                const svn_fs_id_t *id,
                                apr_pool_t *pool)
{
  node_revision_t *noderev;

  SVN_ERR(svn_fs_fs__get_node_revision(&noderev, fs, id, pool, pool));

  /* Delete any mutable property representation. */
  if (noderev->prop_rep && is_txn_rep(noderev->prop_rep))
    SVN_ERR(svn_io_remove_file2(svn_fs_fs__path_txn_node_props(fs, id, pool),
                                FALSE, pool));

  /* Delete any mutable data representation. */
  if (noderev->data_rep && is_txn_rep(noderev->data_rep)
      && noderev->kind == svn_node_dir)
    {
      fs_fs_data_t *ffd = fs->fsap_data;
      SVN_ERR(svn_io_remove_file2(svn_fs_fs__path_txn_node_children(fs, id,
                                                                    pool),
                                  FALSE, pool));

      /* remove the corresponding entry from the cache, if such exists */
      if (ffd->txn_dir_cache)
        {
          const char *key = svn_fs_fs__id_unparse(id, pool)->data;
          SVN_ERR(svn_cache__set(ffd->txn_dir_cache, key, NULL, pool));
        }
    }

  return svn_io_remove_file2(svn_fs_fs__path_txn_node_rev(fs, id, pool),
                             FALSE, pool);
}