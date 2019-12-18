#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_6__ {int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {scalar_t__ kind; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  svn_fs_base__dag_check_mutable (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_dir_entries (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_node (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_remove_node (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__dag_delete_if_mutable(svn_fs_t *fs,
                                   const svn_fs_id_t *id,
                                   const char *txn_id,
                                   trail_t *trail,
                                   apr_pool_t *pool)
{
  dag_node_t *node;

  /* Get the node. */
  SVN_ERR(svn_fs_base__dag_get_node(&node, fs, id, trail, pool));

  /* If immutable, do nothing and return immediately. */
  if (! svn_fs_base__dag_check_mutable(node, txn_id))
    return SVN_NO_ERROR;

  /* Else it's mutable.  Recurse on directories... */
  if (node->kind == svn_node_dir)
    {
      apr_hash_t *entries;
      apr_hash_index_t *hi;

      /* Loop over hash entries */
      SVN_ERR(svn_fs_base__dag_dir_entries(&entries, node, trail, pool));
      if (entries)
        {
          apr_pool_t *subpool = svn_pool_create(pool);
          for (hi = apr_hash_first(pool, entries);
               hi;
               hi = apr_hash_next(hi))
            {
              void *val;
              svn_fs_dirent_t *dirent;

              svn_pool_clear(subpool);
              apr_hash_this(hi, NULL, NULL, &val);
              dirent = val;
              SVN_ERR(svn_fs_base__dag_delete_if_mutable(fs, dirent->id,
                                                         txn_id, trail,
                                                         subpool));
            }
          svn_pool_destroy(subpool);
        }
    }

  /* ... then delete the node itself, any mutable representations and
     strings it points to, and possibly its node-origins record. */
  return svn_fs_base__dag_remove_node(fs, id, txn_id, trail, pool);
}